/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/05 17:30:05 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*ft_execve(t_input *in, t_fd fd)
{
	char	**arenv;
	t_input	*tmp;

	arenv = NULL;
	tmp = in;
	arenv = arenvlst(tmp->env);
	tmp = find_tok(tmp, command, false);
	fprintf(stderr, "\033[0;35m\033[1m#---------- EXECVE ----------#\n\033[0m");
	print_in_node(tmp, &fd, "execve");
	fprintf(stderr, "\033[0;35m\033[1m#----------------------------#\n\033[0m");
	if (tmp->data[0] && access(tmp->data[0], R_OK) != -1)
		printf("execve = %d\n", execve(tmp->data[0], tmp->data, arenv));
	exe_failure(&fd, in, arenv);
	fprintf(stderr, "\033[0;35m\033[1m#----------------------------#\n\033[0m");
	exit(EXIT_FAILURE);
}

static void	*redir_exec(t_input *in, t_fd *fd)
{
	t_input	*tmp;

	tmp = in;
	if (pipe_true(tmp))
		pip_redir(tmp, fd);
	if (op_true(tmp, inredir) && op_true(tmp, command))
		in_redir(fd, tmp);
	if (op_true(tmp, outredir))
		out_redir(fd, tmp);
	if (op_true(tmp, command))
		if (!ft_execve(in, *fd))
			return (print_error(errno, "failure in execve"));
	return ("OK");
}

static void	*create_child(t_input *in, t_fd *fd)
{
	t_input	*tmp;

	tmp = in;
	fprintf(stderr, "PID : %d\n", getpid());
	if (pipe_true(tmp))
	{
		if (pipe(fd->pfd) == -1)
			return (print_error(errno, "opening pipe in exec_cmd"));
		print_fds(fd);
	}
	fd->pid = fork();
	if (fd->pid == -1)
		return (print_error(errno, "opening fork in exec_cmd"));
	return ("OK");
}

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;

	init_fds(&fd);
	tmp = in;
	while (tmp)
	{
		if (tmp && fd.pid == -1)
		{
			if (!create_child(in, &fd))
				return (print_error(errno, NULL));
		}
		if (tmp && fd.pid == 0)
			if (!redir_exec(tmp, &fd))
				return (print_error(errno, NULL));
		tmp = find_next_pipe(tmp);
		if (dup2(fd.pfd[R], fd.tmpin) == -1)
			return (print_error(errno, "duplicating pipe[R] in child"));
		close_fds(&fd, EXE_OK);
	}
	while (wait(0) != -1 && errno != ECHILD);
	if (close(fd.tmpin) == -1)
		print_error(0, "failed to close tmpin");
	return ("fckdat");
}

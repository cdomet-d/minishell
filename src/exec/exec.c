/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/04 18:49:55 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*ft_execve(t_input *in, t_fd fd)
{
	char	**arenv;
	t_input	*tmp;

	arenv = NULL;
	tmp = in;
	fprintf(stderr, "\033[0;35m\033[1m#---------- EXECVE ----------#\n\033[0m");
	arenv = arenvlst(tmp->env);
	tmp = find_tok(tmp, command);
	print_in_node(tmp);
	fprintf(stderr, "\033[0;35m\033[1m#----------------------------#\n\033[0m");
	if (tmp->data[0] && access(tmp->data[0], R_OK) != -1)
		execve(tmp->data[0], tmp->data, arenv);
	close_fds(&fd, EXE_ERR);
	free_dtab(arenv);
	print_error(errno, NULL);
	fprintf(stderr, "\033[0;35m\033[1m#----------------------------#\n\033[0m");
	exit(EXIT_FAILURE);
}

static void	*redir_exec(t_input *in, t_fd fd)
{
	t_input	*tmp;

	fprintf(stderr, "\033[0;35m\033[1m#---------- REDIRS ----------#\n\033[0m");
	tmp = in;
	if (pipe_true(tmp))
		pip_redir(&fd);
	if (op_true(tmp, inredir) && op_true(tmp, command))
		in_redir(&fd, tmp);
	if (op_true(tmp, outredir))
		out_redir(&fd, tmp);
	if (op_true(tmp, command))
		if (!ft_execve(in, fd))
			return (print_error(errno, "failure in execve"));
	if (dup2(fd.tmpin, fd.pfd[R]) == -1)
		return (print_error(errno, "duplicating pipe[R] in child"));
	return ("OK");
}

static void	*create_child(t_input *in, t_fd *fd)
{
	t_input	*tmp;

	fprintf(stderr, "\033[0;35m\033[1m#---------- CCHILD ----------#\n\033[0m");
	tmp = in;
	if (pipe_true(tmp))
	{
		if (pipe(fd->pfd) == -1)
			return (print_error(errno, "opening pipe in exec_cmd"));
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
		if (fd.pid == -1)
			if (!create_child(in, &fd))
				return (print_error(errno, NULL));
		if (fd.pid == 0)
			if (!redir_exec(in, fd))
				return (print_error(errno, NULL));
		close_fds(&fd, EXE_OK);
		tmp = find_next_pipe(tmp);
	}
	while (wait(0) != -1 && errno != ECHILD)
		;
	if (fd.tmpin != 0)
		close(fd.tmpin);
	return ("fckdat");
}

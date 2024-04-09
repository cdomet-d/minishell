/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/07 22:53:52 by jauseff          ###   ########lyon.fr   */
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
	if (tmp->data[0] && access(tmp->data[0], R_OK) != -1)
		printf("execve = %d\n", execve(tmp->data[0], tmp->data, arenv));
	exe_failure(&fd, in, arenv);
	exit(0);
}

static void	*redir_exec(t_input *in, t_fd *fd)
{
	t_input	*tmp;

	tmp = in;
	if (fd->pnb != 0)
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

static void	*create_child(t_fd *fd)
{
	fprintf(stderr, "PID : %d\n", getpid());
	if (fd->pnb != 0)
		if (pipe(fd->pfd) == -1)
			return (print_error(errno, "opening pipe in exec_cmd"));
	fd->pid = fork();
	if (fd->pid == -1)
		return (print_error(errno, NULL));
	return ("OK");
}

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;

	init_fds(&fd);
	tmp = in;
	fd.pnb = count_pipes(tmp);
	while (tmp)
	{
		if (fd.pid != 0)
			if (!create_child(&fd))
				return (print_error(errno, NULL));
		if (tmp && fd.pid == 0)
			if (!redir_exec(tmp, &fd))
				return (print_error(errno, NULL));
		if (fd.pnb != 0)
			fd.pnb--;
		tmp = find_next_pipe(tmp, &fd);
		if (dup2(fd.pfd[R], fd.tmpin) == -1)
			return (print_error(errno, "duplicating pipe[R]"));
		close_pfd(&fd);
	}
	while (wait(0) != -1 && errno != ECHILD)
		;
	return ("fckdat");
}

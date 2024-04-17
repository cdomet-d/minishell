/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/17 18:03:38 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*ft_execve(t_input *in, t_fd fd)
{
	char	**arenv;
	t_input	*tmp;

	(void)fd;
	arenv = NULL;
	tmp = in;
	arenv = arenvlst(tmp->env);
	if (!arenv)
		(print_error(errno, "Failed to allocate arenv in execve"));
	tmp = find_tok(tmp, command, false);
	if (tmp->data[0] && access(tmp->data[0], R_OK) != -1)
	{
		// fprintf(stderr, "\033[0;32m%.20s\033[0m\n", "-- execve ---------------------------------");
		execve(tmp->data[0], tmp->data, arenv);
	}
	print_error(errno, tmp->data[0]);
	if (arenv)
		free_dtab(arenv);
	return ((int *)false);
}

static void	*redir_exec(t_input *in, t_fd *fd)
{
	t_input	*tmp;

	tmp = in;
	if (fd->pnb != 0)
		if (!pip_redir(tmp, fd))
			return (NULL);
	if (op_true(tmp, inredir))
		if (!in_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, outredir))
		if (!out_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, append))	
		if (!app_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, command))
		ft_execve(tmp, *fd);
	return ((int *)false);
}

static void	*create_child(t_fd *fd)
{
	// fprintf(stderr, "%.20s\n", "-- create_child ------------------");
	if (fd->pnb != 0)
	{
		// fprintf(stderr, "%.20s\n", "-- pipe ------------------");
		if (pipe(fd->pfd) == -1)
			return (print_error(errno, "create_child (piping)"));
	}
	fd->pid = fork();
	{
		// fprintf(stderr, "%.20s\n", "-- fork ------------------");
		if (fd->pid == -1)
			return (print_error(errno, "create_child (forking)"));
	}
	return ("OK");
}

static void	wait_for_children(void)
{
	while (wait(0) != -1 && errno != ECHILD)
		;
}

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;

	init_fds(&fd);
	tmp = in;
	fd.pnb = count_pipes(tmp);
	// pmin(tmp, "in main");
	if (op_true(tmp, heredoc))
		create_hdocs(&fd, in);
	while (tmp)
	{
		if (fd.pid != 0)
			if (!create_child(&fd))
				return (print_error(errno, "exec_cmd (create_child)"));
		if (tmp && fd.pid == 0)
			if (!redir_exec(tmp, &fd))
				exe_failure(&fd, in, NULL);
		// fprintf(stderr, "pipes remaining : %ld\n", fd.pnb);
		if (fd.pnb != 0)
		{
			fd.pnb--;
			if (fd.tmpin != -1)
				if (close(fd.tmpin) == -1)
					print_error(errno, "close_exec (tmpin)");
			fd.tmpin = fd.pfd[R];
			close_pipe_write(&fd);
		}
		tmp = find_next_pipe(tmp, &fd);
	}
	if (count_pipes(in))
	{
		close_pipe_read(&fd);
	}
	wait_for_children();
	return ((int *)true);
}

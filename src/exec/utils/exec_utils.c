/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:05:08 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/06 17:12:51 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_and_wait(t_input *in, t_fd *fd)
{
	struct stat infos;
	
	if (count_pipes(in))
		close_pipe_read(fd);
	while (waitpid(0, &in->status, 0) != -1 && errno != ECHILD)
		;
	if (WIFEXITED(in->status))
	{
		if (in->status == 256)
		{
			if (access(in->data[0], X_OK) == -1)
				in->status = 127;
			if (access(in->data[0], X_OK) != -1)
				in->status = 1;
			else if (stat(in->data[0], &infos) != -1)
			{
				if (S_ISDIR(infos.st_mode))
					in->status = 126;
			}
			return ;
		}
	}
	else if (!WIFEXITED(in->status))
		in->status = 128 + g_sig;
}

void	*create_child(t_input *in, t_fd *fd)
{
	if (fd->pnb != 0 && (op_true(in, command) || builtin_true(in)))
	{
		// fprintf(stderr, "%.20s\n", "-- pipe ------------------");
		if (pipe(fd->pfd) == -1)
			return (print_error(errno, "create_child (piping)"));
	}
	if (op_true(in, command) || (builtin_true(in) && fd->pnb != 0))
	{
		// fprintf(stderr, "%.20s\n", "-- fork ------------------");
		fd->pid = fork();
		if (fd->pid == -1)
			return (print_error(errno, "create_child (forking)"));
	}
	return ((int *)true);
}

void	*save_pipin(t_fd *fd)
{
	fd->pnb--;
	if (fd->tmpin != -1)
		if (close(fd->tmpin) == -1)
			print_error(errno, "close_exec (tmpin)");
	fd->tmpin = fd->pfd[R];
	close_pipe_write(fd);
	return ((int *)true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:05:08 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/07 18:20:14 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_and_wait(t_input *in, t_fd *fd)
{
	struct stat infos;
	int	*e_stat;
	
	e_stat = &in->status;
	if (count_pipes(in))
		close_pipe_read(fd);
	waitpid(fd->pid, e_stat, 0);
	while (wait(0) != -1 && errno != ECHILD)
		;
	if (WIFEXITED(*e_stat))
	{
		fprintf(stderr, "%.20s\n", "-- WIFEXITED ------------------");
		fprintf(stderr, "in status : {%d}\n", in->status);
		if (in->status == 256)
		{
			if (access(in->data[0], X_OK) == -1)
			{
				fprintf(stderr, "%.20s\n", "Can't access");
				in->status = 127;
			}
			if (access(in->data[0], X_OK) != -1)
			{
				fprintf(stderr, "%.20s\n", "Can access but couldn't execute");
				in->status = 1;
			}
			else if (stat(in->data[0], &infos) != -1)
			{
				fprintf(stderr, "%.20s\n", "Other access error");
				if (S_ISDIR(infos.st_mode))
					in->status = 126;
			}
		fprintf(stderr, "%.20s\n", "-------------------------------------");
			return ;
		}
	}
	else if (!WIFEXITED(*e_stat))
	{
		fprintf(stderr, "%.20s\n", "-- !WIFEXITED ------------------");
		fprintf(stderr, "in status : {%d}\n", in->status);
		if (in->status == 1)
			return ;
		if (in->status != 2)
		{
			in->status = 1;
			return ;
		}
		in->status = 128 + g_sig;
		fprintf(stderr, "%.20s\n", "-------------------------------------");
	}
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

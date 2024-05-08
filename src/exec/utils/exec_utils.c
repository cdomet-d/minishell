/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:05:08 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/08 19:00:23 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_input *get_last_node(t_input    *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	close_and_wait(t_input *in, t_fd *fd)
{
	struct stat	infos;
	t_input		*last;
	int			e_stat;
	
	if (count_pipes(in))
		close_pipe_read(fd); 
	e_stat = in->status;
	waitpid(fd->pid, &e_stat, 0);
	while (wait(0) != -1 && errno != ECHILD)
		;
	last = get_last_node(in);
	if (WIFEXITED(e_stat))
	{
		if (e_stat == 256)
		{
			// fprintf(stderr, "%.20s\n", "-- w/out signals ------------------");
			if (builtin_true(last))
				in->status = 1;
			else if (access(last->data[0], X_OK) != -1)
			{
				// fprintf(stderr, "%.20s\n", "-- exist but couldnt execute ------------------");
				if (last->data[1] && access(last->data[1], X_OK) == -1)
					in->status = 1;
				else if (stat(last->data[0], &infos) != -1)
				{
					// fprintf(stderr, "%.20s\n", "-- IS_DIR ------------------");
					if (S_ISDIR(infos.st_mode))
						in->status = 126;
				}
				return ;
			}
			else if (access(last->data[0], X_OK) == -1)
			{
				// fprintf(stderr, "%.20s\n", "-- cmd doesnt exist ------------------");
				in->status = 127;
				return ;
			}
			return ;
		}
	}
	else if (!WIFEXITED(e_stat))
	{
		// fprintf(stderr, "%.20s\n", "-- w/ signals ------------------");
		// printf("exit status : {%d}\n", in->status);
		if (in->status == 1)
			return ;
		in->status = 128 + g_sig;
	}
	return ;
}

void	*create_child(t_input *in, t_fd *fd)
{
	if (fd->pnb != 0 && (op_true(in, command) || builtin_true(in)))
	{
		// // fprintf(stderr, "%.20s\n", "-- pipe ------------------");
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
	// fprintf(stderr, "%.20s\n", "-- save pipin ------------------");
	fd->pnb--;
	if (fd->tmpin != -1)
		if (close(fd->tmpin) == -1)
			print_error(errno, "close_exec (tmpin)");
	fd->tmpin = fd->pfd[R];
	close_pipe_write(fd);
	return ((int *)true);
}

void	init_rv(t_input *in)
{
	t_input	*head;
	int		status;

	head = in;
	// pmin(in, NULL);
	status = in->status;
	while (in)
	{
		in->status = status;
		in = in->next;
	}
	in = head;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:05:08 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/18 14:06:17 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	wait_for_children(void)
{
	while (wait(0) != -1 && errno != ECHILD)
		;
}

void	*create_child(t_fd *fd)
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
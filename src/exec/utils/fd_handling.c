/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:39:05 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/17 18:01:58 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_fds(t_fd *fd)
{
	fd->pfd[R] = -1;
	fd->pfd[W] = -1;
	fd->hfd = -1;
	fd->ffd = -1;
	fd ->tmpin = -1;
	fd->pid = -1;
}

void	close_pipe_read(t_fd *fd)
{
	// fprintf(stderr, "%.20s\n", "-- close_pfd[R] ------------------");
	if (close(fd->pfd[R]) == -1)
		print_error(errno, "close_read (pfd[R])");
}

void	close_pipe_write(t_fd *fd)
{
	// fprintf(stderr, "%.20s\n", "-- close_pfd[W] ------------------");
	if (close(fd->pfd[W]) == -1)
		print_error(errno, "close_write (pfd[W])");
}

void	close_pfd(t_fd *fd)
{
	close_pipe_read(fd);
	close_pipe_write(fd);
	init_fds(fd);
}

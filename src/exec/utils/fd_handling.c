/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:39:05 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/17 11:53:59 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_fds(t_fd *fd)
{
	fd->pfd[R] = 0;
	fd->pfd[W] = 0;
	fd->hfd = 0;
	fd->ffd = 0;
	fd ->tmpin = -1;
	fd->pid = -1;
}

void	close_pfd(t_fd *fd)
{
	// fprintf(stderr, "%.20s\n", "-- close_pfd ------------------");
	if (fd->pfd[R] != 0)
		if (close(fd->pfd[R]) == -1)
			print_error(0, "close_pfd (fd->pfd[R])");
	if (fd->pfd[W] != 0)
		if (close(fd->pfd[W]) == -1)
			print_error(0, "close_pfd (fd->pfd[W])");
	init_fds(fd);
}

void	close_tmpin(t_input *in, t_fd *fd)
{
	if (count_pipes(in) > 0)
	{
		fprintf(stderr, "%.20s\n", "-- close_tmpin ------------------");
		if (close(fd->pfd[R]) == -1)
			print_error(errno, "close_tmpin (tmpin)");
	}
	init_fds(fd);
}

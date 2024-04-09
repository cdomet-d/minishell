/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:39:05 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/07 22:54:08 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_fds(t_fd *fd)
{
	fd->pfd[R] = 0;
	fd->pfd[W] = 0;
	fd->ffd = 0;
	fd->pid = -1;
	fd ->tmpin = 1000;
}

void	close_pfd(t_fd *fd)
{
	if (fd->pfd[R] != 0)
		if (close(fd->pfd[R]) == -1)
			print_error(0, "failed to close fd->pfd[R]");
	if (fd->pfd[W] != 0)
		if (close(fd->pfd[W]) == -1)
			print_error(0, "failed to close fd->pfd[W]");
	init_fds(fd);
}

void	close_tmpin(t_input *in, t_fd *fd)
{
	if (count_pipes(in) > 0)
		if (close(fd->tmpin) == -1)
			print_error(0, "failed to close tmpin");
	init_fds(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:39:05 by jauseff           #+#    #+#             */
/*   Updated: 2024/05/22 18:32:05 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_fds(t_fd *fd, t_input *in)
{
	if (in)
		fd->pnb = count_pipes(in);
	fd->pfd[R] = -1;
	fd->pfd[W] = -1;
	fd->hfd = -1;
	fd->ffd = -1;
	fd ->tmpin = -1;
	fd->pid = -1;
}

void	close_pipe_read(t_fd *fd)
{
	if (fd->pfd[R] != -1)
		if (close(fd->pfd[R]) == -1)
			print_error(errno, "close_read (pfd[R])");
}

void	close_pipe_write(t_fd *fd)
{
	if (fd->pfd[W] != -1)
		if (close(fd->pfd[W]) == -1)
			print_error(errno, "close_write (pfd[W])");
}

void	close_pfd(t_fd *fd)
{
	close_pipe_read(fd);
	close_pipe_write(fd);
	init_fds(fd, NULL);
}

void	reset_stds(int tmpstdin, int tmpstdout)
{
	fprintf(stderr, "%.20s\n", "-- resetstds --------------------------");
	if (dup2(tmpstdin, STDIN_FILENO) == -1)
		print_error(errno, "reset_stds (reopening STDIN)");
	if (dup2(tmpstdout, STDOUT_FILENO) == -1)
		print_error(errno, "reset_stds (reopening STDOUT)");
	if (close(tmpstdin) == -1)
		print_error(errno, "reset_stds (closing tmpstdin)");
	if (close(tmpstdout) == -1)
		print_error(errno, "reset_stds (closing tmpstdin)");
}

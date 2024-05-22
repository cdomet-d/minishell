/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/22 11:40:47 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_fds(t_fd *fd)
{
	fprintf(stderr, "%.20s\n pfd[R] - %d || pfd[W] - %d || ffd - %d || tmpin = %d || fd.pnb = %ld\n", "-- fds --------------------------",
	fd->pfd[R], fd->pfd[W], fd->ffd, fd->tmpin, fd->pnb);
}

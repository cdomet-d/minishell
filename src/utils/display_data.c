/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/08 18:18:04 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_fds(t_fd *fd)
{
	fprintf(stderr, "%.20s\npfd[R] - %d || pfd[W] - %d || tmpin = %d || fd.pnb = %ld\n", \
	"-- fds --------------------------", fd->pfd[R],
		fd->pfd[W], fd->tmpin, fd->pnb);
}

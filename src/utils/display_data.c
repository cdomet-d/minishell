/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/24 13:56:06 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_ops(t_op count)
{
	fprintf(stderr, "\033[0;34m\033[1m\n#-------- Redirections --------#\n\033[0m");
	if (count.pip)
		fprintf(stderr, "%-18s %-5s %-2d\n", "  pipes", "> Y", count.pip);
	else
		fprintf(stderr, "%-18s %-5s\n", "  pipes", "> N");
	if (count.inredir)
		fprintf(stderr, "%-18s %-5s\n", "  In redirection", "> Y");
	else
		fprintf(stderr, "%-18s %-5s\n", "  In redirection", "> N");
	if (count.outredir)
		fprintf(stderr, "%-18s %-5s\n", "  Out redirection", "> Y");
	else
		fprintf(stderr, "%-18s %-5s\n", "  Out redirection", "> N");
	fprintf(stderr, "\033[0;34m\033[1m#------------------------------#\n\n\033[0m");
}

void	print_fds(t_fd *fd)
{
	fprintf(stderr, "%.20s\n", "== fds =================================");
	fprintf(stderr, "pfd[R] - %d || pfd[W] - %d || tmpin = %d\n", fd->pfd[R],
		fd->pfd[W], fd->tmpin);
}

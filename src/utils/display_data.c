/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/04 14:25:47 by cdomet-d         ###   ########lyon.fr   */
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
	fprintf(stderr, "\033[0;35m\033[1m#---------- EXECVE ----------#\n\033[0m");
	fprintf(stderr, "\033[0;34m\033[1m\n#-------- FDS ------------#\n\033[0m");
	fprintf(stderr, "%-21s%d\n", "  fd->pfd[R]", fd->pfd[R]);
	fprintf(stderr, "%-21s%d\n", "  fd->pfd[W]", fd->pfd[W]);
	fprintf(stderr, "%-21s%d\n", "  fd->tmpin", fd->tmpin);
	fprintf(stderr, "%-21s%d\n", "  fd->ffd", fd->ffd);
	fprintf(stderr, "%-21s%d\n", "  fd->pid", fd->pid);
	fprintf(stderr, "\033[0;34m\033[1m#--------------------------#\n\n\033[0m");
}

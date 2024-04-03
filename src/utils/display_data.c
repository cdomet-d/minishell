/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/03 17:22:18 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_ops(t_op count)
{
	printf("\033[0;34m\033[1m\n#-------- Redirections --------#\n\033[0m");
	if (count.pip)
		printf("%-18s %-5s %-2d\n", "  pipes", "> Y", count.pip);
	else
		printf("%-18s %-5s\n", "  pipes", "> N");
	if (count.inredir)
		printf("%-18s %-5s\n", "  In redirection", "> Y");
	else
		printf("%-18s %-5s\n", "  In redirection", "> N");
	if (count.outredir)
		printf("%-18s %-5s\n", "  Out redirection", "> Y");
	else
		printf("%-18s %-5s\n", "  Out redirection", "> N");
	printf("\033[0;34m\033[1m#------------------------------#\n\n\033[0m");
}

void	print_fds(t_fd *fd)
{
	printf("\033[0;34m\033[1m\n#------------- FDS ------------#\n\033[0m");
	printf("%-21s%d\n", "  fd->pfd[R]", fd->pfd[R]);
	printf("%-21s%d\n", "  fd->pfd[W]", fd->pfd[W]);
	printf("%-21s%d\n", "  fd->tmpin", fd->tmpin);
	printf("%-21s%d\n", "  fd->ffd", fd->ffd);
	printf("%-21s%d\n", "  fd->pid", fd->pid);
	printf("\033[0;34m\033[1m#------------------------------#\n\n\033[0m");
}

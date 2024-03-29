/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/29 14:06:22 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_ops(t_op count)
{
	printf("\033[0;34m\033[1m\n#---- Redirections ----#\n\033[0m");
	printf("Pipes > %d\n", count.pip);
	if (count.inredir)
		printf("In redirection : yes\n");
	else
		printf("In redirection : no\n");
	if (count.outredir)
		printf("Out redirection : yes\n");
	else
		printf("Out redirection : no\n");
	printf("\033[0;34m\033[1m#-----------------------#\n\n\033[0m");
}

void	print_fds(t_fd *fd)
{
	printf("\033[0;34m\033[1m\n#--------- FDS --------#\n\033[0m");
	printf("%-20s%d\n", "  fd->pfd[R] :", fd->pfd[R]);
	printf("%-20s%d\n", "  fd->pfd[W] : ", fd->pfd[W]);
	printf("%-20s%d\n", "  fd->tmpin : ", fd->tmpin);
	printf("%-20s%d\n", "  fd->ffd : ", fd->ffd);
	printf("%-20s%d\n", "  fd->pid : ", fd->pid);
	printf("\033[0;34m\033[1m#-----------------------#\n\n\033[0m");
}

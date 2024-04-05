/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:42:06 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/05 10:16:56 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*out_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	fprintf(stderr, "\033[0;35m\033[1m#---------- OUTRED ----------#\n\033[0m");
	tmp = find_tok(in, outredir);
	print_in_node(tmp);
	fd->ffd = open(tmp->data[0], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd->ffd == -1)
		return (print_error(errno, in->data[0]));
	if (dup2(fd->ffd, STDOUT_FILENO) == -1)
		return (print_error(errno, "duping out to file"));
	if (fd->ffd != 0)
		close(fd->ffd);
	close(fd->ffd);
	return ("fdat");
}

void	*in_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	fprintf(stderr, "\033[0;35m\033[1m#---------- INREDI ----------#\n\033[0m");
	tmp = find_tok(in, inredir);
	if (access(tmp->data[0], R_OK) == -1)
	{
		print_error(errno, NULL);
		fd->ffd = open("/dev/null", O_RDONLY);
		if (fd->ffd == -1)
			return (print_error(errno, "opening /dev/null"));
	}
	else
		fd->ffd = open(tmp->data[0], O_RDONLY);
	print_in_node(tmp);
	if (fd->ffd == -1)
		return (print_error(errno, "opening infile"));
	if (dup2(fd->ffd, STDIN_FILENO) == -1)
		return (print_error(errno, "duping in to file"));
	close(fd->ffd);
	return ("fdat");
}

void	*pip_redir(t_input *tmp, t_fd *fd)
{
	fprintf(stderr, "\033[0;35m\033[1m#---------- PIPRE ----------=#\n\033[0m");
	if (is_first_pipe(tmp))
	{
		if (dup2(fd->pfd[R], STDIN_FILENO) == -1)
			return (print_error(errno, "duping tempin to in"));
	}
	if (dup2(fd->tmpin, STDIN_FILENO) == -1)
		return (print_error(errno, "duping tempin to in"));
	if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
		return (print_error(errno, "duping pipe[out] to out"));
	close (fd->pfd[R]);
	close (fd->pfd[W]);
	return ("hellya");
}

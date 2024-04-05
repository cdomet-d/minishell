/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:42:06 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/05 17:18:29 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*out_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	tmp = find_tok(in, outredir, false);
	print_in_node(tmp, fd, "outredir");
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

	tmp = find_tok(in, inredir, false);
	if (access(tmp->data[0], R_OK) == -1)
	{
		print_error(errno, NULL);
		fd->ffd = open("/dev/null", O_RDONLY);
		if (fd->ffd == -1)
			return (print_error(errno, "opening /dev/null"));
	}
	else
		fd->ffd = open(tmp->data[0], O_RDONLY);
	print_in_node(tmp, fd, "inredir");
	if (fd->ffd == -1)
		return (print_error(errno, "opening infile"));
	if (dup2(fd->ffd, STDIN_FILENO) == -1)
		return (print_error(errno, "duping in to file"));
	close(fd->ffd);
	return ("fdat");
}

void	*pip_redir(t_input *tmp, t_fd *fd)
{
	if (is_first_cmd(tmp))
	{
		print_in_node(tmp, fd, "piperedir : first cmd");
		if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
			return (print_error(errno, "duping pipe[out] to out"));
	}
	tmp = find_tok(tmp, command, true);
	if (is_last_cmd(tmp))
	{
		print_in_node(tmp, fd, "pipredir : last cmd");
		if (dup2(fd->tmpin, STDIN_FILENO) == -1)
			return (print_error(errno, "duping tmpin to in"));
	}
	else
	{
		print_in_node(tmp, fd, "pipredir : inbetween cmd");
		if (dup2(fd->tmpin, STDIN_FILENO) == -1)
			return (print_error(errno, "duping tmpin to in"));
		if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
			return (print_error(errno, "duping pipe[out] to out"));
		
	}
	if (close (fd->pfd[W]) == - 1)
		print_error(0, "couldn't close fd->pfd[W]");
	return ("hellya");
}

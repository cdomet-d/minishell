/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:42:06 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/12 18:08:25 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*out_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	tmp = find_tok(in, outredir, false);
	while (op_true(tmp, outredir))
	{
		fprintf(stderr, "%.20s\n", "-- outredir -----------------------------");
		fd->ffd = open(tmp->data[0], O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (fd->ffd == -1)
			return (print_error(errno, "outredir (opening out)"));
		if (op_true(in, command))
			if (dup2(fd->ffd, STDOUT_FILENO) == -1)
				return (print_error(errno, "outredir (duping out)"));
		if (close(fd->ffd) == -1)
			return (print_error(errno, "outredir (closing out)"));
		tmp = find_tok(tmp, outredir, true);
	}
	return ((int *)true);
}

void	*app_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	tmp = find_tok(in, append, false);
	while (op_true(tmp, append))
	{
		fprintf(stderr, "%.20s\n", "-- appredir -----------------------------");
		fd->ffd = open(tmp->data[0], O_CREAT | O_APPEND | O_RDWR, 0777);
		if (fd->ffd == -1)
			return (print_error(errno, "appredir (opening out)"));
		if (op_true(in, command))
			if (dup2(fd->ffd, STDOUT_FILENO) == -1)
				return (print_error(errno, "appredir (duping out)"));
		if (close(fd->ffd) == -1)
			return (print_error(errno, "appredir (closing out)"));
		tmp = find_tok(tmp, append, true);
	}
	return ((int *)true);
}

void	*in_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	tmp = find_tok(in, inredir, false);
	while (op_true(tmp, inredir))
	{
		fprintf(stderr, "%.20s\n", "-- inredir ------------------------------");
		if (access(tmp->data[0], R_OK) == -1)
		{
			print_error(errno, NULL);
			fd->ffd = open("/dev/null", O_RDONLY);
			if (fd->ffd == -1)
				return (print_error(errno, "inredir (opening /dev/null)"));
		}
		else
			fd->ffd = open(tmp->data[0], O_RDONLY);
		if (fd->ffd == -1)
			return (print_error(errno, "inredir (opening in)"));
		if (dup2(fd->ffd, STDIN_FILENO) == -1)
			return (print_error(errno, "inredir (duping in"));
		close(fd->ffd);
		tmp = find_tok(tmp, inredir, true);
	}
	return ((int *)true);
}

void	*pip_redir(t_input *tmp, t_fd *fd)
{
	fprintf(stderr, "%.20s\n", "-- pipredir ---------------------------------");
	if (is_first_cmd(tmp))
	{
		if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
			return (print_error(errno, "pip_redir (ifc, pipe[W] to out"));
	}
	else if (is_last_cmd(tmp))
	{
		if (dup2(fd->tmpin, STDIN_FILENO) == -1)
			return (print_error(errno, "pip_redir (ilc, tmpin to in"));
	}
	else if (!is_first_cmd(tmp) && !is_last_cmd(tmp))
	{
		if (dup2(fd->tmpin, STDIN_FILENO) == -1)
			return (print_error(errno, "pip_redir (else, tmpin to in"));
		if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
			return (print_error(errno, "pip_redir (else, pfd[W] to out"));
	}
	close_pfd(fd);
	return ((int *)true);
}

void	*h_redir(t_fd *fd, t_input *in)
{
	fprintf(stderr, "%.20s\n", "-- h_redir -----------------------------------");
	create_hfile(fd, in);
	if (dup2(fd->hfd, STDIN_FILENO) == -1)
	{
		if (close (fd->hfd) == -1)
			return (print_error(errno, "h_redir (closing hfd)"));
		return (print_error(errno, "h_redir (duping hdf to in)"));
	}
	if (close (fd->hfd) == -1)
		return (print_error(errno, "h_redir (closing hfd)"));
	return ((int *) true);
}

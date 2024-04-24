/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:42:06 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/24 15:10:11 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*out_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	fprintf(stderr, "%.20s\n", "-- outredir -----------------------------");
	tmp = find_tok(in, outredir, false);
	if (!tmp)
		return (print_error(0, "minishell: no such token"));
	if (tmp->data[1])
		return (print_error(0, "minishell: ambiguous redirection"));
	while (op_true(tmp, outredir))
	{
		fd->ffd = open(tmp->data[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd->ffd == -1)
			return (print_error(errno, "outredir (opening out)"));
		if (op_true(in, command) || builtin_true(in))
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

	fprintf(stderr, "%.20s\n", "-- appredir -----------------------------");
	tmp = find_tok(in, append, false);
	if (!tmp)
		return (print_error(0, "minishell: no such token"));
	if (tmp->data[1])
		return (print_error(0, "minishell: ambiguous redirection"));
	while (op_true(tmp, append))
	{
		fd->ffd = open(tmp->data[0], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd->ffd == -1)
			return (print_error(errno, "appredir (opening out)"));
		if (op_true(in, command) || builtin_true(in))
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

	fprintf(stderr, "%.20s\n", "-- inredir ------------------------------");
	tmp = find_tok(in, inredir, false);
	if (!tmp)
		return (print_error(0, "minishell: no such token"));
	if (tmp->data[1])
		return (print_error(0, "minishell: ambiguous redirection"));
	while (op_true(tmp, inredir))
	{
		fd->ffd = open(tmp->data[0], O_RDONLY);
		if (fd->ffd == -1)
		{
			print_error(errno, "inredir (opening in)");
			fd->ffd = open("/dev/null", O_RDONLY);
			if (fd->ffd == -1)
				return (print_error(errno, "inredir (opening /dev/null)"));
		}
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
	if (is_first(tmp))
	{
		if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
			return (print_error(errno, "pip_redir (ifc, pipe[W] to out"));
	}
	else if (is_last(tmp))
	{
		if (dup2(fd->tmpin, STDIN_FILENO) == -1)
			return (print_error(errno, "pip_redir (ilc, tmpin to in"));
	}
	else if (!is_first(tmp) && !is_last(tmp))
	{
		if (dup2(fd->tmpin, STDIN_FILENO) == -1)
			return (print_error(errno, "pip_redir (else, tmpin to in"));
		if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
			return (print_error(errno, "pip_redir (else, pfd[W] to out"));
	}
	if (fd->pid == 0 && fd->tmpin != -1)
	{
		if (close(fd->tmpin) == -1)
			print_error(errno, "close_exec (tmpin)");
		close_pfd(fd);
	}
	return ((int *)true);
}

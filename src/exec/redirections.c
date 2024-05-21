/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:42:06 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/21 16:39:23 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*out_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	tmp = find_tok(in, outredir, false);
	if (!tmp)
		tmp = find_tok(in, append, false);
	if (tmp && tmp->data[1])
		return (print_error(0, "minishell: ambiguous redirection"));
	while (tmp && tmp->tok != pip && (op_true(tmp, outredir) || \
		op_true(tmp, append)))
	{
		if (tmp->tok == outredir)
			fd->ffd = open(tmp->data[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (tmp->tok == append)
			fd->ffd = open(tmp->data[0], O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd->ffd == -1)
			return (verror("minishell: ", tmp->data[0], \
		": permission denied"), NULL);
		if (op_true(in, command) || builtin_true(in))
			if (dup2(fd->ffd, STDOUT_FILENO) == -1)
				return (print_error(errno, "minishell: exec"));
		if (close(fd->ffd) == -1)
			return (print_error(errno, "minishell: exec"));
		tmp = tmp->next;
	}
	return ((int *)true);
}

void	*in_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	tmp = find_tok(in, inredir, false);
	if (!tmp)
		return (NULL);
	if (tmp->data[1])
		return (print_error(0, "minishell: ambiguous redirection"));
	while (op_true(tmp, inredir))
	{
		if (!open_infiles(fd, tmp))
			return (NULL);
		tmp = find_tok(tmp, inredir, true);
	}
	return ((int *)true);
}

void	*here_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	tmp = in;
	if (op_true(tmp, inredir))
		tmp = find_tok(in, inredir, false);
	else if (op_true(tmp, heredoc))
		tmp = find_tok(in, heredoc, false);
	if (!tmp)
		return (print_error(0, "minishell: exec"));
	if (tmp->data[1])
		return (print_error(0, "minishell: ambiguous redirection"));
	while (op_true(tmp, heredoc))
	{
		if (!open_infiles(fd, tmp))
			return (NULL);
		tmp = find_tok(tmp, heredoc, true);
	}
	return ((int *)true);
}

void	*pip_redir(t_input *tmp, t_fd *fd)
{
	if (is_first(tmp))
	{
		if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
			return (print_error(errno, "minishell: exec"));
	}
	else if (is_last(tmp))
	{
		if (dup2(fd->tmpin, STDIN_FILENO) == -1)
			return (print_error(errno, "minishell: exec"));
	}
	else if (!is_first(tmp) && !is_last(tmp))
	{
		if (dup2(fd->tmpin, STDIN_FILENO) == -1)
			return (print_error(errno, "minishell: exec"));
		if (dup2(fd->pfd[W], STDOUT_FILENO) == -1)
			return (print_error(errno, "minishell: exec"));
	}
	if (fd->pid == 0)
	{
		if (fd->tmpin != -1)
			if (close(fd->tmpin) == -1)
				print_error(errno, "minishell: exec");
		close_pfd(fd);
	}
	return ((int *)true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:42:06 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/22 17:01:02 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_input	*find_redir(t_input	*in, bool next)
{
	t_input	*tmp;

	tmp = in;
	if (!tmp)
		return (NULL);
	if (tmp && tmp->tok == pip)
		tmp = tmp->next;
	if (next)
		tmp = tmp->next;
	while (tmp && tmp->tok != pip)
	{
		if (tmp->tok == append || tmp->tok == outredir || tmp->tok == inredir || tmp->tok == heredoc)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	*redir_all_in_pipe(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	
	tmp = find_redir(in, false);
	if (tmp && tmp->data[1])
		return (print_error(0, "minishell: ambiguous redirection"));
	while (tmp && tmp->tok != pip)
	{
		if (tmp->tok == inredir || tmp->tok == heredoc)
		{
			if (!open_infiles(fd, tmp))
				return (NULL);
		}
		else if (tmp->tok == outredir || tmp->tok == append)
		{
			if (!open_outfiles(fd, tmp))
				return (NULL);
		}
		tmp = tmp->next;
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

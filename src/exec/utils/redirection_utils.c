/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:44:46 by jauseff           #+#    #+#             */
/*   Updated: 2024/05/22 11:58:33 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_first(t_input *in)
{
	t_input	*tmp;
	bool	first;

	tmp = in;
	first = true;
	if (tmp->prev == NULL)
		return (first);
	while (tmp)
	{
		if (tmp && tmp->tok == pip)
		{
			first = false;
		}
		tmp = tmp->prev;
	}
	return (first);
}

bool	is_last(t_input *in)
{
	t_input	*tmp;
	bool	last;

	tmp = in;
	last = true;
	if (tmp->next == NULL)
		return (last);
	while (tmp)
	{
		tmp = tmp->next;
		if (tmp && tmp->tok == pip)
		{
			last = false;
		}
	}
	return (last);
}

void	*open_infiles(t_fd *fd, t_input *tmp)
{
	fd->ffd = open(tmp->data[0], O_RDONLY);
	if (tmp->tok == heredoc)
		unlink(tmp->data[0]);
	if (fd->ffd == -1)
	{
		if (errno == ENOENT)
			return (verror("minishell: ", tmp->data[0], \
			": no such file or directory"), NULL);
		else if (errno == EACCES)
			return (verror("minishell: ", tmp->data[0], \
			": permission denied"), NULL);
		else
			return (verror("minishell: ", tmp->data[0], \
			": error opening file"), NULL);
	}
	if (dup2(fd->ffd, STDIN_FILENO) == -1)
		return (print_error(errno, "open_infile (duping fd to STDIN)"));
	if (close(fd->ffd) == -1)
		return (print_error(errno, "minishell: exec: closing out"));	
	return ((int *)true);
}

void	*open_outfiles(t_fd *fd, t_input *tmp)
{
	if (tmp->tok == outredir)
			fd->ffd = open(tmp->data[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (tmp->tok == append)
		fd->ffd = open(tmp->data[0], O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd->ffd == -1)
		return (verror("minishell: ", tmp->data[0], ": permission denied"), NULL);
	if (dup2(fd->ffd, STDOUT_FILENO) == -1)
		return (print_error(errno, "minishell: exec: duping out"));
	if (close(fd->ffd) == -1)
		return (print_error(errno, "minishell: exec: closing out"));
	return ((int *)true);
}
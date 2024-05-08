/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:44:46 by jauseff           #+#    #+#             */
/*   Updated: 2024/05/08 19:18:52 by jauseff          ###   ########lyon.fr   */
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
		tmp = tmp->prev;
		if (tmp && (builtin_true(tmp) || tmp->tok == command))
			first = false;
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
		if (tmp && (builtin_true(tmp) || tmp->tok == command))
			last = false;
	}
	return (last);
}

void	*open_infiles(t_fd *fd, t_input *tmp)
{
	fd->ffd = open(tmp->data[0], O_RDONLY);
	if (tmp->tok == heredoc)
		unlink(tmp->data[0]);
	if (fd->ffd == -1)
		return (NULL);
	if (dup2(fd->ffd, STDIN_FILENO) == -1)
		return (print_error(errno, "open_infile (duping fd to STDIN)"));
	close(fd->ffd);
	return ((int *)true);
}

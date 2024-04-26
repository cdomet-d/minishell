/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:44:46 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/26 17:12:37 by cdomet-d         ###   ########lyon.fr   */
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
		if (tmp && (tmp->tok == builtin_true(in) || tmp->tok == command))
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
		if (tmp && (tmp->tok == builtin_true(in) || tmp->tok == command))
			last = false;
	}
	return (last);
}

void	*open_infiles(t_fd *fd, t_input *tmp)
{
	fd->ffd = open(tmp->data[0], O_RDONLY);
	if (op_true(tmp, heredoc))
		unlink(tmp->data[0]);
	if (fd->ffd == -1)
	{
		print_error(errno, tmp->data[0]);
		fd->ffd = open("/dev/null", O_RDONLY);
		if (fd->ffd == -1)
			return (NULL);
	}
	if (dup2(fd->ffd, STDIN_FILENO) == -1)
		return (NULL);
	close(fd->ffd);
	return ((int *)true);
}

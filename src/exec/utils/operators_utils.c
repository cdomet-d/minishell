/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:19:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/07 13:58:58 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	count_pipes(t_input *in)
{
	t_input	*tmp;
	size_t	npip;

	npip = 0;
	tmp = in;
	while (tmp)
	{
		if (tmp->tok == pip)
			npip++;
		tmp = tmp->next;
	}
	if (npip == 0)
		return (npip);
	return (npip + 1);
}

bool	op_true(t_input *in, t_tok op)
{
	t_input	*tmp;

	tmp = in;
	while (tmp && tmp->tok != pip)
	{
		if (tmp->tok == op)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_input	*find_tok(t_input	*in, t_tok op, bool next)
{
	t_input	*tmp;

	tmp = in;
	if (!tmp)
		return (NULL);
	if (next)
		tmp = tmp->next;
	while (tmp && tmp->tok != pip)
	{
		if (tmp->tok == op)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_input	*find_next_pipe(t_input	*in, t_fd *fd)
{
	t_input	*tmp;

	tmp = in;
	if (fd->pnb <= 0)
		return (NULL);
	while (tmp && tmp->tok != pip)
		tmp = tmp->next;
	tmp = tmp->next;
	return (tmp);
}

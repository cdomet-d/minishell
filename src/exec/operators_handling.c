/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:19:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/04 17:21:57 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	pipe_true(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp)
	{
		if (tmp->tok == pip)
			return (true);
		tmp = tmp->next;
	}
	return (false);
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

t_input	*find_tok(t_input	*in, t_tok op)
{
	t_input	*tmp;

	tmp = in;
	while (tmp && tmp->tok != op)
		tmp = tmp->next;
	return (tmp);
}

t_input	*find_next_pipe(t_input	*in)
{
	t_input	*tmp;

	tmp = in;
	if (!tmp)
		return (NULL);
	if (tmp && !pipe_true(tmp))
		return (NULL);
	while (tmp && tmp->tok != pip)
		tmp = tmp->next;
	tmp = tmp->next;
	return (tmp);
}

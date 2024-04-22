/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:44:46 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/22 17:14:47 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_first(t_input *in, t_tok token)
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
		if (tmp && tmp->tok == token)
			first = false;
	}
	return (first);
}

bool	is_last(t_input *in, t_tok token)
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
		if (tmp && tmp->tok == token)
			last = false;
	}
	return (last);
}

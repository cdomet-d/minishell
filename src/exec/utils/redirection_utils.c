/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:44:46 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/24 13:30:42 by cdomet-d         ###   ########lyon.fr   */
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

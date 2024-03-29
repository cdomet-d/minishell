/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:27:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/26 16:01:33 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_redirs(t_input *in, t_op *counter)
{
	t_input	*head;

	counter->pip = 0;
	head = in;
	while (in)
	{
		if (in->tok == pip)
			counter->pip++;
		in = in->next;
	}
	in = head;
	count_brackets(in, counter);
}

void	count_brackets(t_input *in, t_op *counter)
{
	t_input	*head;

	counter->inredir = 0;
	counter->outredir = 0;
	head = in;
	while (in && in->tok != pip)
	{
		if (in->tok == inredir)
			counter->inredir++;
		if (in->tok == outredir)
			counter->outredir++;
		in = in->next;
	}
	in = head;
}

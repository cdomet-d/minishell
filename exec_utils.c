/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:27:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/25 18:13:34 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_pipes(t_input *in, t_redir *redir)
{
	t_input	*head;

	head = in;
	while (in)
	{
		if (in->tok == pip)
			redir->pip++;
		in = in->next;
	}
	in = head;
}

size_t	count_redirs(t_input *in)
{
	t_input	*head;
	size_t	counter;

	counter = 0;
	head = in;
	while (in->tok != pip)
	{
		if (in->tok == inredir)
			counter++;
		if (in->tok == outredir)
			counter++;
		in = in->next;
	}
	in = head;
	return (counter);
}

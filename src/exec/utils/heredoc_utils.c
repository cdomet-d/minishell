/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:39:51 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/10 18:11:05 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	here_true(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp)
	{
		if (tmp->tok == heredoc)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_input	*find_here(t_input	*in, bool next)
{
	t_input	*tmp;

	tmp = in;
	if (tmp == NULL)
		return (NULL);
	if (next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->tok == heredoc)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_delim(t_input *in)
{
	char	*tmpdel;

	tmpdel = ft_strdup(in->data[0]);
	if (!tmpdel)
		return (print_error(errno, NULL));
	if (in->data[0][0] < 0)
		tmpdel[0] *= -1;
	return (tmpdel);
}

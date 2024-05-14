/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:54:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/14 14:24:39 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	not_num(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}


void	mh_exit(char *line, t_input *in)
{
	unsigned long long int	rv;

	if (ft_dstrlen(in->data) > 2)
	{
		print_error(E2BIG, "bash: exit");
		return ;
	}
	if (line)
		free(line);
	if (in && in->data[1])
	{
		rv = ft_atoll(in->data[1]);
		if (!not_num(in->data[1]) || rv > EXIT_MAX)
		{
			parsing_error("minishell: exit: ", in->data[1], ": numeric argument\
			required");
			rv = 2;
		}
		fatal_exit(&in, rv, NULL);
	}
	rv = in->status;
	fatal_exit(&in, rv, NULL);
}

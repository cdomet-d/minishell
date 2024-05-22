/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:54:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/21 19:38:50 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	overflow(char *str)
{
	char	too_big[20];
	size_t	i;

	i = 0;
	ft_strlcpy(too_big, "9223372036854775807", 20);
	if (!str)
		return (true);
	if (ft_strlen(str) > ft_strlen(too_big))
		return (false);
	if (ft_strlen(str) == ft_strlen(too_big))
	{
		if (str[i] > too_big[i])
			return (false);
		i++;
	}
	return (true);
}

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

static void	is_invalid_arg(t_input *in, unsigned long long int rv)
{
	if (not_num(in->data[1]) == 0 || overflow(in->data[1]) == 0)
	{
		verror("minishell: exit: ", in->data[1], \
		": numeric argument required");
		rv = 2;
		fatal_exit(&in, rv, NULL);
	}
}

int	mh_exit(char **line, t_input *in)
{
	unsigned long long int	rv;

	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (in && in->data[1])
	{
		is_invalid_arg(in, 0);
		if (ft_dstrlen(in->data) > 2)
			return (print_error(E2BIG, "minishell: exit: "), 1);
		else
		{
			rv = ft_atoll(in->data[1]);
			in->status = (unsigned char)rv;
			return (fatal_exit(&in, in->status, NULL), in->status);
		}
	}
	rv = in->status;
	return (fatal_exit(&in, rv, NULL), rv);
}

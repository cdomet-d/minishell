/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:22:42 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/23 19:34:42 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	len_str(char *str)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1]
				&& (str[i + 1] == '"' || str[i + 1] == '\''))
			|| str[i] == '\'' || str[i] == '"')
			i++;
		else if (str[i])
		{
			i++;
			len++;
		}
	}
	return (len);
}

static void	fill_str(char *new, char *str)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1]
				&& (str[i + 1] == '"' || str[i + 1] == '\''))
			|| str[i] == '\'' || str[i] == '"')
			i++;
		else if (str[i])
			new[j++] = str[i++];
	}
}

char	*rm_quotes(char *str)
{
	char		*new;
	size_t		len;

	put_in_neg(str, '\'', '"');
	len = len_str(str);
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (print_error(errno, NULL));
	fill_str(new, str);
	return (new);
}

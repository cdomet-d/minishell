/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:22:42 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/23 18:45:29 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	len_str(char *str)
{
	int		i;
	int		len;
	char	quotetype;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			quotetype = str[i++];
			while (str[i] && str[i] != quotetype)
			{
				i++;
				len++;
			}
			i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	fill_str(char *new, char *str)
{
	int		i;
	int		j;
	char	quotetype;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			quotetype = str[i++];
			while (str[i] && str[i] != quotetype)
				new[j++] = str[i++];
			i++;
		}
		else
			new[j++] = str[i++];
	}
}

char	*rm_quotes(char *str)
{
	char	*new;
	int		len;

	len = len_str(str);
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (NULL);
	fill_str(new, str);
	return (new);
}

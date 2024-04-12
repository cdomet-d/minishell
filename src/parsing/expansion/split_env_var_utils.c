/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:08:33 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/11 20:08:53 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_word(char *new, char *old, int i)
{
	int	j;

	j = 0;
	while (old[j] && i > 0)
	{
		new[j] = old[j];
		j++;
		i--;
	}
}

int	nb_letter_str(char *data, int *j, int letter)
{
	char	quotetype;

	while (data[*j] && (data[*j] == ' '
			|| (data[*j] >= '\t' && data[*j] <= '\r')))
		*j += 1;
	while (data[*j] && data[*j] != ' ' && (data[*j] < '\t' || data[*j] > '\r'))
	{
		if (data[*j] == '"' || data[*j] == '\'')
		{
			quotetype = data[*j];
			*j += 1;
			letter += 1;
			while (data[*j] && data[*j] != quotetype)
			{
				letter += 1;
				*j += 1;
			}
		}
		if (data[*j])
		{
			letter += 1;
			*j += 1;
		}
	}
	return (letter);
}

void	put_in_neg(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '"')
		{
			i++;
			while (data[i] && data[i] != '"')
				i++;
		}
		if (data[i] == '\'')
		{
			data[i++] *= -1;
			while (data[i] && data[i] != '\'')
				data[i++] *= -1;
			data[i++] *= -1;
		}
		else if (data[i])
			i++;
	}
}

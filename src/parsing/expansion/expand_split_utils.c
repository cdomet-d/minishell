/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:08:33 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/23 19:35:34 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	put_in_neg(char *data, char quote1, char quote2)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == quote1)
		{
			i++;
			while (data[i] && data[i] != quote1)
				i++;
		}
		if (data[i] == quote2)
		{
			i++;
			while (data[i] && data[i] != quote2)
				data[i++] *= -1;
		}
		if (data[i])
			i++;
	}
}

int	check_ws(char **tab)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		if (!tab[i][j])
			return (1);
		while (tab[i][j])
		{
			if (tab[i][j] == '$'
				&& (tab[i][j + 1] == '"' || tab[i][j + 1] == '\''))
				return (1);
			if (tab[i][j] == '"')
				while (tab[i][j] && tab[i][j] != '"')
					j++;
			if (tab[i][j] == ' ' || (tab[i][j] >= '\t' && tab[i][j] <= '\r'))
				return (1);
			if (tab[i][j])
				j++;
		}
		i++;
	}
	return (0);
}

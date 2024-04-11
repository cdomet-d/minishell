/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:08:33 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/09 16:40:15 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_word(char *new, char *old, int i)
{
	int	j;

	j = 0;
	while (old[j] && i > 0)
	{
		if (old[j] < 0)
			old[j] *= -1;
		new[j] = old[j];
		j++;
		i--;
	}
}

int	nb_letter_str(char *data, int *j, int letter)
{
	while (data[*j] && (data[*j] == ' '
			|| (data[*j] >= '\t' && data[*j] <= '\r')))
		*j += 1;
	while (data[*j] && data[*j] != ' ' && (data[*j] < '\t' || data[*j] > '\r'))
	{
		if (data[*j] && data[*j] == '"')
		{
			*j += 1;
			letter += 1;
			while (data[*j] && data[*j] != '"')
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

char	**nb_letter(char **data, char **newtab)
{
	int	i;
	int	j;
	int	word;
	int	letter;

	i = 0;
	word = 0;
	while (data[i])
	{
		j = 0;
		while (data[i][j])
		{
			letter = nb_letter_str(data[i], &j, 0);
			newtab[word] = ft_calloc(sizeof(char), letter + 1);
			if (!newtab[word])
				return (free_dtab(newtab), NULL);
			fill_word(newtab[word], data[i] + (j - letter), letter);
			word += 1;
			if (data[i][j])
				j++;
		}
		i++;
	}
	return (newtab);
}

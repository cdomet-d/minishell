/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:28:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/24 17:16:59 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	nb_letter_str(char *data, int *j, int letter)
{
	while (data[*j] && (data[*j] == ' '
			|| (data[*j] >= '\t' && data[*j] <= '\r')))
		*j += 1;
	while (data[*j] && data[*j] != ' ' && (data[*j] < '\t' || data[*j] > '\r'))
	{
		if (data[*j] == '"')
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

static char	**split_tab(char **data, char **newtab)
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
				return (free_dtab(newtab), print_error(errno, NULL));
			ft_strlcpy(newtab[word], data[i] + (j - letter), letter + 1);
			word += 1;
			if (data[i][j])
				j++;
		}
		i++;
	}
	return (newtab);
}

static void	nb_word(char **tab, int *word)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '"')
			{
				while (tab[i][j] && tab[i][j] != '"')
					j++;
			}
			if ((tab[i][j] != ' ' && (tab[i][j] < '\t' || tab[i][j] > '\r'))
				&& (tab[i][j + 1] == ' ' || (tab[i][j + 1] >= '\t'
						&& tab[i][j + 1] <= '\r') || tab[i][j + 1] == '\0'))
				*word += 1;
			if (tab[i][j])
				j++;
		}
		i++;
	}
}

char	**expand_split(char **data, t_env **env, int rv)
{
	char	**newtab;
	char	**temp;
	int		word;

	newtab = NULL;
	temp = NULL;
	word = 0;
	temp = expand(data, env, rv);
	if (!temp)
		return (NULL);
	if (!check_ws(temp))
		return (temp);
	nb_word(temp, &word);
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (free_dtab(temp), print_error(errno, NULL));
	newtab = split_tab(temp, newtab);
	if (!newtab)
		return (free_dtab(temp), NULL);
	free_dtab(temp);
	return (newtab);
}

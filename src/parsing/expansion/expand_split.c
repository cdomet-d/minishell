/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:28:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/13 16:33:09 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	nb_letter_str(char *data, size_t *j, size_t letter)
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
	size_t	i;
	size_t	j;
	size_t	word;
	size_t	letter;

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
				return (free_dtab(newtab), \
				print_error(errno, "minishell: parsing"));
			ft_strlcpy(newtab[word], data[i] + (j - letter), letter + 1);
			word += 1;
			if (data[i][j])
				j++;
		}
		i++;
	}
	return (newtab);
}

static void	nb_word(char **tab, size_t *word)
{
	size_t	i;
	size_t	j;

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

char	**expand_split(char **data, t_env **env, int status)
{
	char	**newtab;
	char	**temp;
	size_t	word;

	newtab = NULL;
	temp = NULL;
	word = 0;
	temp = expand(data, env, status);
	if (!temp)
		return (NULL);
	if (!check_ws(temp))
		return (temp);
	nb_word(temp, &word);
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (free_dtab(temp), print_error(errno, "minishell: parsing"));
	newtab = split_tab(temp, newtab);
	if (!newtab)
		return (free_dtab(temp), NULL);
	free_dtab(temp);
	return (newtab);
}

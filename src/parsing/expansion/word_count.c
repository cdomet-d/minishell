/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:08:48 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/11 19:22:37 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_replace(char **data, t_env **env, int rv)
{
	int		word;
	int		letter;
	char	**newtab;

	word = 0;
	newtab = NULL;
	while (data[word])
		word++;
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (NULL);
	word = 0;
	while (data[word])
	{
		letter = letters(data[word], env);
		newtab[word] = ft_calloc(sizeof(char), letter + 1);
		if (!newtab[word])
			return (free_dtab(newtab), NULL);
		ft_copy(data[word], newtab[word], env, rv);
		word++;
	}
	newtab[word] = NULL;
	return (newtab);
}

void	nb_word_str(char *newtab, int *word)
{
	int		j;
	char	quotetype;

	j = 0;
	while (newtab[j])
	{
		if (newtab[j] == '"' || newtab[j] == '\'')
		{
			quotetype = newtab[j++];
			while (newtab[j] && newtab[j] != quotetype)
				j++;
		}
		if ((newtab[j] != ' ' && (newtab[j] < '\t' || newtab[j] > '\r'))
			&& (newtab[j + 1] == ' ' || (newtab[j + 1] >= '\t'
					&& newtab[j + 1] <= '\r') || newtab[j + 1] == '\0'))
			*word += 1;
		if (newtab[j])
			j++;
	}
}

char	**nb_word(char **data, t_env **env, int *word, int rv)
{
	char	**newtab;
	int		i;

	i = 0;
	while (data[i])
	{
		put_in_neg(data[i]);
		i++;
	}
	i = 0;
	newtab = ft_replace(data, env, rv);
	if (!newtab)
		return (NULL);
	while (newtab[i])
	{
		nb_word_str(newtab[i], word);
		i++;
	}
	return (newtab);
}

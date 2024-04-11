/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:28:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/11 19:48:12 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

char	**expand(char **data, t_env **env, int rv)
{
	char	**newtab;
	char	**temp;
	int		word;

	newtab = NULL;
	temp = NULL;
	word = 0;
	temp = nb_word(data, env, &word, rv);
	if (!temp)
		return (NULL);
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (NULL);
	newtab = nb_letter(temp, newtab);
	if (!newtab)
		return (NULL);
	free_dtab(temp);
	return (newtab);
}

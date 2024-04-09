/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:28:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/04 19:47:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_replace(char **data, t_env **env)
{
	int word;
	int		letter;
	char    **newtab;

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
		ft_copy(data[word], newtab[word], env);
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
	quotetype = 0;
	while (newtab[j])
	{
		if (newtab[j] == '\'' || newtab[j] == '"')
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

char	**nb_word(char **data, t_env **env, int *word)
{
	char	**newtab;
	int		i;

	i = 0;
	newtab = ft_replace(data, env);
	if (!newtab)
		return (NULL);
	while (newtab[i])
	{
		nb_word_str(newtab[i], word);
		i++;
	}
	return (newtab);
}

int	expand(t_input *node, t_env **env)//, int fd)
{
	char	**newtab;
	char	**temp;
	int		word;

	newtab = NULL;
	temp = NULL;
	word = 0;
	temp = nb_word(node->data, env, &word);
	if (!temp)
		return (1);
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (1);
	newtab = nb_letter(temp, newtab);
	if (!newtab)
		return (1);
	free_dtab(node->data);
	node->data = newtab;
	free_dtab(temp);
	return (0);
}

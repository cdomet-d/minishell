/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:28:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/02 18:51:27 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//si $arg=NULL ou n'existe pas replace par rien

void	nb_word_env(char *str, int *word)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i])
	{
		if ((str[i] != ' ' && (str[i] < '\t' || str[i] > '\r'))
			&& (str[i + 1] == '\0' || str[i + 1] == ' ' || (str[i + 1] >= '\t'
					&& str[i + 1] <= '\r')))
			*word += 1;
		i++;
	}
	*word -= 1;
}

void	nb_word(char **data, t_env **env, int *word)
{
	int		i;
	int		j;
	char	quotetype;

	i = 0;
	while (data[i])
	{
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] == '"' || data[i][j] == '\'')
			{
				quotetype = data[i][j++];
				while (data[i][j] && data[i][j] != quotetype)
					j++;
			}
			if (data[i][j] == '$')
				nb_word_env(search_env(data[i] + (j + 1), env), word);
			if (data[i][j])
				j++;
		}
		*word += 1;
		i++;
	}
}

void	nb_letter_env(char *str, int *letter)
{
	(void)str;
	(void)letter;
}

void	nb_letter(char *str, t_env **env, int *letter)
{
	while (str[*letter])
	{
		if (str[*letter] == '\'')
		{
			*letter += 1;
			while (str[*letter] && str[*letter] != '\'')
				*letter += 1;
		}
		if (str[*letter] == '"')
		{
			*letter += 1;
			while (str[*letter] && str[*letter] != '"')
			{
				if (str[*letter] == '$')
					nb_letter_env(search_env(str + (*letter + 1), env), letter);
				*letter += 1;
			}
		}
		if (str[*letter] == '$')
			nb_letter_env(search_env(str + (*letter + 1), env), letter);
		if (str[*letter])
			*letter += 1;
	}
}

int	expand(t_input *node, t_env **env)
{
	char	**newtab;
	char	**temp;
	int		word;
	int		letter;

	newtab = NULL;
	temp = NULL;
	word = 0;
	nb_word(node->data, env, &word);
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (1);
	word = 0;
	while (node->data[word])
	{
		letter = 0;
		nb_letter(node->data[word], env, &letter);
		newtab = ft_calloc(sizeof(char), letter + 1);
		if (!newtab)
			return (1);
		ft_fill();
		word++;
	}
	temp = node->data;
	node->data = NULL;
	free_dtab(node->data);
	return (0);
}

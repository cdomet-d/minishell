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

void	fill_env_quote(char *env, char *new, int *letter)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	while (env[i])
	{
		new[*letter] = env[i]; 
		*letter += 1;
		i++;
	}
}

void	fill_env(char *env, char **newtab, int *word, int *letter)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	while (env[i])
	{
		if (env[i] && (env[i] == ' ' || (env[i] >= '\t' && env[i] <= '\r')))
		{
			while (env[i] && (env[i] == ' ' || (env[i] >= '\t' && env[i] <= '\r')))
				i++;
			if (env[i])
			{
				*letter = 0;
				*word += 1;
			}
		}
		if (env[i])
		{
			newtab[*word][*letter] = env[i];
			i++;
			*letter += 1;
		}
	}
}

void	ft_fill(char **data, t_env **env, char **newtab)
{
	int	i;
	int	j;
	int	word;
	int	letter;

	i = 0;
	word = 0;
	while (data[i])
	{
		letter = 0;
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] == '\'')
			{
				newtab[word][letter++] = data[i][j++];
				while (data[i][j] && data[i][j] != '\'')
					newtab[word][letter++] = data[i][j++];
			}
			if (data[i][j] == '"')
			{
				newtab[word][letter++] = data[i][j++];
				while (data[i][j] && data[i][j] != '"')
				{
					if (data[i][j] == '$')
					{
						j++;
						fill_env_quote(search_env(data[i] + j, env), newtab[word], &letter);
						while (data[i][j] && data[i][j] != '$' && data[i][j] != '"'
							&& data[i][j] != '\'' && data[i][j] != ' '
							&& (data[i][j] < '\t' || data[i][j] > '\r'))
							j++;
					}
					else if (data[i][j])
						newtab[word][letter++] = data[i][j++];
				}
			}
			if (data[i][j] && data[i][j] == '$')
			{
				j++;
				fill_env(search_env(data[i] + j, env), newtab, &word, &letter);
				while (data[i][j] && data[i][j] != '$' && data[i][j] != '"'
					&& data[i][j] != '\'')
					j++;
			}
			else if (data[i][j])
				newtab[word][letter++] = data[i][j++];
		}
		i++;
		word++;
	}
}

int	expand(t_input *node, t_env **env, int fd)
{
	char	**newtab;
	// char	**temp;
	// char	**dup;
	int		word;

	newtab = NULL;
	// dup = NULL;
	// temp = NULL;
	word = 0;
	// dup = tab_dup(node->data);
	// if (!dup)
	// 	return (1);
	newtab = nb_word(/*dup, */node->data, env, &word);
	if (!newtab)
		return (1);
	dprintf(fd, "%d\n", word);
	int	i = 0;
	while (newtab[i])
	{
		printf("len : %ld\n", strlen(newtab[i]));
		printf("newtab : %s\n", newtab[i++]);
	}
	free_dtab(newtab);
	// newtab = ft_calloc(sizeof(char *), word + 1);
	// if (!newtab)
	// 	return (1);
	// word = 0;
	// nb_letter(node->data, env, newtab, word, fd);
	// ft_fill(node->data, env, newtab);
	// temp = node->data;
	// node->data = NULL;
	// node->data = newtab;
	// free_dtab(temp);
	return (0);
}

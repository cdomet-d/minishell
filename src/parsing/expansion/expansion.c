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

// #include <fcntl.h>
// #include <stdio.h>
int	expand(t_input *node, t_env **env)//, int fd)
{
	// char	**newtab;
	// char	**temp;
	int		word;
	// int		letter;
	// int		i;
	// int		j;

	// newtab = NULL;
	// temp = NULL;
	word = 0;
	nb_word(node->data, env, &word);
	printf("word : %d\n", word);
	// newtab = ft_calloc(sizeof(char *), word + 1);
	// if (!newtab)
	// 	return (1);
	// word = 0;
	// i = 0;
	// while (node->data[i])
	// {
	// 	j = 0;
	// 	letter = 0;
	// 	while (node->data[i][j])
	// 	{
	// 		nb_letter(node->data[i], env, &letter, &j);
	// 		if (node->data[i][j] && node->data[i][j] == '$')
	// 		{
	// 			j++;
	// 			if (nb_letter_env(search_env(node->data[i] + j, env), &letter, &word, newtab))
	// 				return (free_dtab(newtab), 1);
	// 			while (node->data[i][j] && node->data[i][j] != '$'
	// 				&& node->data[i][j] != '"' && node->data[i][j] != '\'')
	// 				j++;
	// 		}
	// 		else if (node->data[i][j])
	// 		{
	// 			j++;
	// 			letter++;
	// 		}
	// 	}
	// 	// printf("1 : word : %d letter : %d\n", word, letter);
	// 	newtab[word] = ft_calloc(sizeof(char), letter + 1);
	// 	if (!newtab)
	// 		return (free_dtab(newtab), 1);
	// 	// ft_fill(newtab[word], node->data[i], letter);
	// 	i++;
	// 	word++;
	// }
	// ft_fill(node->data, env, newtab);
	// temp = node->data;
	// node->data = NULL;
	// node->data = newtab;
	// free_dtab(temp);
	return (0);
}

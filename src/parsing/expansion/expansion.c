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

//si $arg=NULL ou n'existe pas replace par rien

void	nb_word_env(char *str, int *word, char c)
{
	int		i;

	(void)c;
	i = 0;
	if (!str/* || !str[0]*/)
		return ;
	printf("str : %s\n", str);
	while (str[i])
	{
		if ((str[i] != ' ' && (str[i] < '\t' || str[i] > '\r'))
			&& (str[i + 1] == '\0' || str[i + 1] == ' ' || (str[i + 1] >= '\t'
					&& str[i + 1] <= '\r')))
			*word += 1;
		i++;
	}
	// if ((str[i - 1] == ' ' || (str[i - 1] >= '\t' && str[i - 1] <= '\r')) && (c == '"' || c == '\''))
	// 	*word += 1;
	*word -= 1;
}

void	nb_word(char **data, t_env **env, int *word)
{
	int		i;
	int		j;
	char	quotetype;
	char	*str;
	// bool	dollar;

	i = 0;
	str = NULL;
	// dollar = false;
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
			{
				str = search_env(data[i] + (j + 1), env);
				// dollar = true;
				// if (j != 0 && data[i][j - 1] > 0 && ((!str || !str[0]) || (str && (str[0] == ' ' || (str[0] >= '\t' && str[0] <= '\r')))))
				// 	*word += 1;
				// j++;
				// while (data[i][j] && data[i][j] != '$' && data[i][j] != '"'
				// 	&& data[i][j] != '\'')
				// {
				// 	data[i][j] *= -1;
				// 	j++;
				// }
				nb_word_env(str, word, data[i][j]);
			}
			// else 
			if (data[i][j])
				j++;
		}
		// if (dollar == false)
		*word += 1;
		i++;
	}
}

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

int	expand(t_input *node, t_env **env)
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

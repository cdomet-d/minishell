/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:28:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/29 19:22:01 by csweetin         ###   ########.fr       */
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
		if ((str[i] != ' ' && str[i] < '\t' && str[i] > '\r')
			&& (str[i + 1] == '\0' || str[i + 1] == ' ' || (str[i + 1] >= '\t'
			&& str[i + 1] <= '\r')))
		{
			// printf("in\n");
			*word += 1;
		}
		i++;
	}
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

void	expand(t_input *node, t_env **env)
{
	// int	i;
	// int	j;
	int	word;
	// int	letter;

	word = 0;
	nb_word(node->data, env, &word);
	printf("word : %d\n", word);
}

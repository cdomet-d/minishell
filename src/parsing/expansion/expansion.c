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

int	str_cmp(char *data, char *env)
{
	int	i;

	i = 0;
	while (data[i] && env[i] && env[i] != '=')
	{
		if (data[i] != env[i])
			return (1);
		i++;
	}
	if (env[i] != '=' || data[i] != '\0')
		return (1);
	return (0);
}

void	search_env(char *data, t_env **env, int *count)
{
	t_env	*node;
	int		i;

	i = 0;
	node = *env;
	while (node)
	{
		if (!strcmp(data, node->env))
		{
			// printf("in\n");
			while (node->env[i] && node->env[i - 1] != '=')
				i++;
			while (node->env[i])
			{	
				while (node->env[i] && (node->env[i] == ' '
					|| (node->env[i] >= '\t' && node->env[i] <= '\r')))
					i++;
				if (((i - 1) == 0 && node->env[i - 1] != ' ' && node->env[i - 1] < '\t' && node->env[i - 1] > '\r')
					&& (node->env[i + 1] == '\0' || (node->env[i + 1] == ' ' || (node->env[i + 1] >= '\t' && node->env[i + 1] <= '\r'))))
				{
					*count += 1;
				}
				if (node->env[i] != '\0')
					i++;
			}
		}
		node = node->next;
	}
}

void	nbr_word(char **data, t_env **env, int *word)
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
				search_env(data[i] + (j + 1), env, word);
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
	nbr_word(node->data, env, &word);
	printf("word : %d\n", word);
}

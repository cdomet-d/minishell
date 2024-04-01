/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:42:17 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/29 17:42:20 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_for_dollar(t_input *node)
{
	int	i;
	int	j;

	i = 0;
	if (!node->data)
		return (0);
	while (node->data[i])
	{
		j = 0;
		while (node->data[i][j])
		{
			if (node->data[i][j] == '\'')
			{
				j++;
				while (node->data[i][j] && node->data[i][j] != '\'')
					j++;
			}
			if (node->data[i][j] == '$')
				return (1);
			if (node->data[i][j])
				j++;
		}
		i++;
	}
	return (0);
}

int	ft_strcmp(char *data, char *env)
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

char	*search_env(char *data, t_env **env)
{
	t_env	*node;
	
	node = *env;
	while (node)
	{
		if (!ft_strcmp(data, node->env))
			return (node->env);
		node = node->next;
	}
	return (NULL);
}
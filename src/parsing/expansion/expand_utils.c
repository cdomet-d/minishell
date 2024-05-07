/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:42:17 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/03 18:26:31 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	search_dollar(char **data)
{
	int	i;
	int	j;

	i = 0;
	if (!data)
		return (0);
	while (data[i])
	{
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] == '$')
				return (1);
			else if (data[i][j])
				j++;
		}
		i++;
	}
	return (0);
}

int	ft_strcmp_env(char *data, char *env)
{
	int	i;

	i = 0;
	while (data[i] && env[i] && env[i] != '='
		&& (ft_isalnum(data[i]) || data[i] == '_'))
	{
		if (data[i] != env[i])
			return (1);
		i++;
	}
	if (env[i] && env[i] != '=')
		return (1);
	if (data[i] && (ft_isalnum(data[i]) || data[i] == '_'))
		return (1);
	return (0);
}

char	*search_env(char *data, t_env **env)
{
	t_env	*node;
	int		i;

	i = 0;
	node = *env;
	while (node)
	{
		if (!ft_strcmp_env(data, node->env))
		{
			while (node->env[i] && node->env[i] != '=')
				i++;
			i++;
			if (node->env[i] == '\0')
				return (NULL);
			return (node->env + i);
		}
		node = node->next;
	}
	return (NULL);
}

void	nb_letter_rv(int *letter, int *j, char *rv)
{
	*j += 1;
	*letter += ft_strlen(rv);
}

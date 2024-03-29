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

void	command_expand()
{

}

char	*search_env(char *data, t_env **env)
{
	char	*var;
	t_env	*node;

	(void)data;
	var = NULL;
	node = *env;
	while (node->env)
	{
		node = node->next;
	}
	return (var);
}

void	op_expand(char *data, t_env **env)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i++] == '\'')
		{
			while (data[i] && data[i] != '\'')
				i++;
		}
		if (data[i] == '$')
			search_env(data + i, env);
		if (data[i])
			i++;
	}
}

void	expand(t_input *node, t_env **env)
{
	(void)env;
	if (node->tok == command)
		command_expand();
	else
		op_expand(node->data[0], env);
}

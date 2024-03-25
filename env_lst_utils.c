/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:33:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 18:04:31 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// all exit are to be replaced with free_all funct.
void	env_addback(t_env **env, t_env *node)
{
	t_env	*last;

	if (!node || !env)
		return ;
	last = env_last(*env);
	if (!last)
		(*env) = node;
	else
	{
		last->next = node;
		node->prev = last;
	}
}

t_env	*env_last(t_env	*env)
{
	if (!env)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

t_env	*env_newnode(t_input *input, char *data)
{
	t_env	*node;

	// disabled for testing;
	(void)input;
	node = malloc(1 * sizeof(t_env));
	if (!node)
		exit(EXIT_FAILURE);
	node->env = ft_strdup(data);
	if (!node->env)
		exit(EXIT_FAILURE);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	env_freelst(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	env = env_last(env);
	while (env)
	{
		free(env->env);
		tmp = env->prev;
		free(env);
		env = tmp;
	}
	env = NULL;
}

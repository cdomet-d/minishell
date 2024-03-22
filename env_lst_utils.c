/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:33:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 15:18:38 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// all exit are to be replaced with free_all funct.
t_env	*env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!new || !env)
		return (NULL);
	last = env_last(*env);
	if (!last)
		(*env) = new;
	else
	{
		last->next = new;
		new->prev = last;
	}
	return (*env);
}

t_env	*env_last(t_env	*env)
{
	if (!env)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

t_env	*env_create_node(t_input *input, char *data)
{
	t_env	*new;

	// disabled for testing;
	(void)input;
	new = malloc(1 * sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);
	new->env = ft_strdup(data);
	if (!new->env)
		exit(EXIT_FAILURE);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	env_free_lst(t_env *env)
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
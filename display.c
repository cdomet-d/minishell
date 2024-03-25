/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 20:10:38 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_for(t_env *env)
{
	t_env	*head;

	head = env;
	printf("==== PRINTING FORWARD ====\n");
	while (env)
	{
		printf("env > %p\nenv->env > %s\nenv->prev > %p\nenv->next > %p\n\n", \
		env, env->env, env->prev, env->next);
		env = env->next;
	}
	env = head;
	printf("==========================\n\n");
}

t_env	*env_last(t_env	*env)
{
	if (!env)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

void	print_env_back(t_env *env)
{
	t_env	*head;

	head = env;
	printf("=== PRINTING BACKWARDS ===\n");
	env = env_last(env);
	printf("env > %p\n", env);
	while (env)
	{
		printf("env > %p\nenv->env > %s\nenv->prev > %p\nenv->next > %p\n\n", \
		env, env->env, env->prev, env->next);
		env = env->prev;
	}
	env = head;
	printf("==========================\n\n");
}

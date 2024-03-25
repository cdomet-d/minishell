/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/25 11:22:17 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_for(t_env *env)
{
	t_env	*head;

	head = env;
	printf("==== PRINTING ENV FORWARD ====\n");
	printf("%p\n", env);
	while (env)
	{
		printf("env->env > %s\n", env->env);
		env = env->next;
	}
	env = head;
	printf("==========================\n\n");
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

void	print_in_for(t_input *input)
{
	t_input	*head;

	head = input;
	printf("==== PRINTING INPUT FORWARD ====\n");
	while (input)
	{
		display_dtab(input->data);
		printf("Token = %u\n", input->tok);
		print_env_for(input->env);
		input = input->next;
	}
	input = head;
	printf("==========================\n\n");
	input = head;
}

void	display_dtab(char **dtab)
{
	size_t	i;

	i = 0;
	while (dtab && dtab[i])
		printf("%s\n", dtab[i++]);
}

t_env	*env_last(t_env	*env)
{
	if (!env)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

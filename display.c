/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/25 17:33:01 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_in_for(t_input *input)
{
	t_input	*head;
	int		node;

	node = 1;
	head = input;
	printf("\033[0;35m\033[1m#==== PRINTING INPUT FORWARD ====#\n\n\033[0m");
	while (input)
	{
		printf("\033[0;34m\033[1m#---- Node %d ----#\n\033[0m", node++);
		display_dtab(input->data);
		printf("token = %u\n", input->tok);
		// print_env_for(input->env);
		input = input->next;
		printf("\033[0;34m\033[1m#----------------#\n\n\033[0m");
	}
	input = head;
	print_redirs(input);
}

void	print_env_for(t_env *env)
{
	t_env	*head;

	head = env;
	printf("==== PRINTING ENV FORWARD ====\n");
	printf("%p\n", env);
	while (env)
	{
		printf("env -> %s\n", env->env);
		env = env->next;
	}
	env = head;
	printf("==========================\n\n");
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

void	print_redirs(t_input *input)
{
	printf("\033[0;34m\033[1m#---- REDIRECTIONS FIRST UNIT ----#\n\033[0m");
	printf("Pipes : %ld\n", count_pipes(input));
	if (count_inredir(input))
		printf("inredir : yes\n");
	else
		printf("inredir : none\n");
	if (count_outredir(input))
		printf("outredir : yes\n");
	else
		printf("outredir : none\n");
	printf("\033[0;34m\033[1m#---------------------------------#\n\n\033[0m");
}

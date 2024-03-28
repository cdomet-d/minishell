/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/28 17:43:41 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		input = input->next;
		printf("\033[0;34m\033[1m#----------------#\n\n\033[0m");
	}
	input = head;
}

void	print_env_for(t_env *env)
{
	t_env	*head;
	size_t	i;

	head = env;
	i = 0;
	printf("==== PRINTING ENV FORWARD ====\n");
	while (env)
	{
		printf("env[%-2ld] > %.25s\n", i, env->env);
		env = env->next;
		i++;
	}
	env = head;
	printf("==========================\n\n");
}

void	display_dtab(char **dtab)
{
	size_t	i;

	i = 0;
	while (dtab && dtab[i])
	{
		printf("tab[%ld] > %s\n", i, dtab[i]);
		i++;
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

void	print_ops(t_op count)
{
	printf("\033[0;34m\033[1m\n#---- Redirections ----#\n\033[0m");
	printf("Pipes > %d\n", count.pip);
	if (count.inredir)
		printf("In redirection : yes\n");
	else
		printf("In redirection : no\n");
	if (count.outredir)
		printf("Out redirection : yes\n");
	else
		printf("Out redirection : no\n");
	printf("\033[0;34m\033[1m#-----------------------#\n\n\033[0m");
}

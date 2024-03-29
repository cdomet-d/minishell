/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/29 17:38:27 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_enum(int token)
{
	if (token == 0)
		printf("%-7s %s\n", "  token", " > pipe");
	else if (token == 1)
		printf("%-7s %s\n", "  token", " > inredir");
	if (token == 2)
		printf("%-7s %s\n", "  token", " > outredir");
	if (token == 3)
		printf("%-7s %s\n", "  token", " > append");
	if (token == 4)
		printf("%-7s %s\n", "  token", "> heredoc");
	if (token == 5)
		printf("%-7s %s\n", "  token", " > command");
}

void	print_in_for(t_input *input)
{
	t_input	*head;
	int		node;

	node = 1;
	head = input;
	printf("\033[0;35m\033[1m\n#==== PRINTING INPUT FORWARD ====#\n\n\033[0m");
	while (input)
	{
		printf("\033[38;5;206m\033[1m#----------- Node %d -----------#\n\033[0m", node++);
		display_dtab(input->data);
		print_enum(input->tok);
		input = input->next;
		printf("\033[38;5;206m\033[1m#------------------------------#\n\n\033[0m");
	}
	printf("\033[0;35m\033[1m#================================#\n\n\033[0m");
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
		printf("env[%2ld] > %.25s\n", i, env->env);
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
		printf("  tab[%02ld] > %s\n", i, dtab[i]);
		i++;
	}
}

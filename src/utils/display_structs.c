/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/29 13:42:37 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_enum(int token)
{
	if (token == 0)
		printf("token > pipe\n");
	else if (token == 1)
		printf("token > inredir\n");
	if (token == 2)
		printf("token > outredir\n");
	if (token == 3)
		printf("token > append\n");
	if (token == 4)
		printf("token > heredoc\n");
	if (token == 5)
		printf("token > command\n");
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
		printf("\033[0;34m\033[1m#---- Node %d ----#\n\033[0m", node++);
		display_dtab(input->data);
		print_enum(input->tok);
		input = input->next;
		printf("\033[0;34m\033[1m#----------------#\n\n\033[0m");
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
		printf("tab[%ld] > %s || len : %ld\n", i, dtab[i], strlen(dtab[i]));
		i++;
	}
}

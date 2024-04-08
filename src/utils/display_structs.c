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

static void	print_enum(int token, int fd)
{
	if (token == 0)
		dprintf(fd, "token > pipe\n");
	else if (token == 1)
		dprintf(fd, "token > inredir\n");
	if (token == 2)
		dprintf(fd, "token > outredir\n");
	if (token == 3)
		dprintf(fd, "token > append\n");
	if (token == 4)
		dprintf(fd, "token > heredoc\n");
	if (token == 5)
		dprintf(fd, "token > command\n");
}

void	print_in_for(t_input *input, int fd)
{
	t_input	*head;
	int		node;

	node = 1;
	head = input;
	// dprintf(fd, "\033[0;35m\033[1m\n#==== PRINTING INPUT FORWARD ====#\n\n\033[0m");
	while (input)
	{
		// dprintf(fd, "\033[0;34m\033[1m#---- Node %d ----#\n\033[0m", node++);
		dprintf(fd, "---- Node %d ----\n", node++);
		display_dtab(input->data, fd);
		print_enum(input->tok, fd);
		input = input->next;
		dprintf(fd, "----------------\n");
		// dprintf(fd, "\033[0;34m\033[1m#----------------#\n\n\033[0m");
	}
	// dprintf(fd, "\033[0;35m\033[1m#================================#\n\n\033[0m");
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

void	display_dtab(char **dtab, int fd)
{
	size_t	i;

	i = 0;
	while (dtab && dtab[i])
	{
		dprintf(fd, "tab[%ld] > %s || len : %ld\n", i, dtab[i], strlen(dtab[i]));
		i++;
	}
}

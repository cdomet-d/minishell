/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/09 17:57:23 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_enum(int token)
{
	if (token == 0)
		fprintf(stderr, "%-7s %s ", "  token", "  > pipe");
	else if (token == 1)
		fprintf(stderr, "%-7s %s ", "  token", "  > inredir");
	if (token == 2)
		fprintf(stderr, "%-7s %s ", "  token", "  > outredir");
	if (token == 3)
		fprintf(stderr, "%-7s %s ", "  token", "  > append");
	if (token == 4)
		fprintf(stderr, "%-7s %s ", "  token", "  > heredoc");
	if (token == 5)
		fprintf(stderr, "%-7s %s ", "  token", "  > command");
}

static void	qpenum(int token)
{
	if (token == 0)
		fprintf(stderr, "%s ", "pipe");
	else if (token == 1)
		fprintf(stderr, "%s ", "inredir");
	if (token == 2)
		fprintf(stderr, "%s ", "outredir");
	if (token == 3)
		fprintf(stderr, "%s ", "append");
	if (token == 4)
		fprintf(stderr, "%s ", "heredoc");
	if (token == 5)
		fprintf(stderr, "%s ", "command");
}

void	print_in_for(t_input *input)
{
	t_input	*head;
	int		node;

	node = 1;
	head = input;
	fprintf(stderr, "\033[0;35m\033[1m\n#==== PRINTING INPUT FORWARD ====#\n\n\033[0m");
	while (input)
	{
		fprintf(stderr, "\033[38;5;206m\033[1m#----------- Node %d -----------#\n\033[0m", node++);
		display_dtab(input->data);
		print_enum(input->tok);
		input = input->next;
		fprintf(stderr, "\033[38;5;206m\033[1m#------------------------------#\n\n\033[0m");
	}
	fprintf(stderr, "\033[0;35m\033[1m#================================#\n\n\033[0m");
	input = head;
}

void	pmin(t_input *input)
{
	t_input	*head;

	head = input;
	fprintf(stderr, "%.20s\n", "-- intoks ------------------");
	while (input)
	{
		qpenum(input->tok);
		input = input->next;
	}
	fprintf(stderr, "%.21s\n", "\n--------------------------------------------\n");
	input = head;
}

void	print_env_for(t_env *env)
{
	t_env	*head;
	size_t	i;

	head = env;
	i = 0;
	fprintf(stderr, "==== PRINTING ENV FORWARD ====\n");
	while (env)
	{
		fprintf(stderr, "env[%2ld] > \033[0;34m%.20s\n\033[0m", i, env->env);
		env = env->next;
		i++;
	}
	env = head;
	fprintf(stderr, "==========================\n\n");
}

void	display_dtab(char **dtab)
{
	size_t	i;

	i = 0;
	while (dtab && dtab[i])
	{
		fprintf(stderr, "  tab[%02ld] > %s\n", i, dtab[i]);
		i++;
	}
}

void	print_in_node(t_input *node, t_fd *fd, char *str)
{
	fprintf(stderr, "\033[38;5;206m\033[1m#----------- Node %d ---------#\n\033[0m", node->no);
	fprintf(stderr, "\033[0;34m| %s |\n\033[0m", str);
	display_dtab(node->data);
	print_enum(node->tok);
	print_fds(fd);
	fprintf(stderr, "\033[38;5;206m\033[1m#----------------------------#\n\033[0m");
}

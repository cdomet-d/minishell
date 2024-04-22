/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_structs_v.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:59:40 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/17 12:07:47 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		fprintf(stderr, "\033[38;5;206m\033[1m\n#------------------------------#\n\n\033[0m");
	}
	fprintf(stderr, "\033[0;35m\033[1m\n#================================#\n\n\033[0m");
	input = head;
}

void	print_enum(int token)
{
	if (token == 0)
		fprintf(stderr, "%-7s %s ", "  token", "  > pipe");
	else if (token == 1)
		fprintf(stderr, "%-7s %s ", "  token", "  > inredir");
	else if (token == 2)
		fprintf(stderr, "%-7s %s ", "  token", "  > outredir");
	else if (token == 3)
		fprintf(stderr, "%-7s %s ", "  token", "  > append");
	else if (token == 4)
		fprintf(stderr, "%-7s %s ", "  token", "  > heredoc");
	else if (token == 5)
		fprintf(stderr, "%-7s %s ", "  token", "  > command");
	else if (token == 6)
		fprintf(stderr, "%-7s %s ", "  token", "  > echo");
	else if (token == 7)
		fprintf(stderr, "%-7s %s ", "  token", "  > cd");
	else if (token == 8)
		fprintf(stderr, "%-7s %s ", "  token", "  > pwd");
	else if (token == 9)
		fprintf(stderr, "%-7s %s ", "  token", "  > export");
	else if (token == 10)
		fprintf(stderr, "%-7s %s ", "  token", "  > unset");
	else if (token == 11)
		fprintf(stderr, "%-7s %s ", "  token", "  > env");
	else if (token == 12)
		fprintf(stderr, "%-7s %s ", "  token", "  > exit");
}

void	print_in_node(t_input *node, t_fd *fd, char *str)
{
	fprintf(stderr, "\033[38;5;206m\033[1m#----------- Node %d ---------#\n\033[0m", node->no);
	fprintf(stderr, "\033[0;34m| %s |\n\033[0m", str);
	display_dtab(node->data);
	print_enum(node->tok);
	(void)fd;
	print_fds(fd);
	fprintf(stderr, "\033[38;5;206m\033[1m#----------------------------#\n\033[0m");
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
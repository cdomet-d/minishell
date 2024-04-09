/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/09 17:42:12 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_enum(int token)
{
	if (token == 0)
		fprintf(stderr, "%-7s %s\n", "  token", "  > pipe");
	else if (token == 1)
		fprintf(stderr, "%-7s %s\n", "  token", "  > inredir");
	if (token == 2)
		fprintf(stderr, "%-7s %s\n", "  token", "  > outredir");
	if (token == 3)
		fprintf(stderr, "%-7s %s\n", "  token", "  > append");
	if (token == 4)
		fprintf(stderr, "%-7s %s\n", "  token", "  > heredoc");
	if (token == 5)
		fprintf(stderr, "%-7s %s\n", "  token", "  > command");
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

void	print_env_for(t_env *env)
{
	t_env	*head;
	size_t	i;

	head = env;
	i = 0;
	fprintf(stderr, "==== PRINTING ENV FORWARD ====\n");
	while (env)
	{
		fprintf(stderr, "env[%2ld] > %.25s\n", i, env->env);
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
		// printf("tab[%ld] > %s --> len : %ld\n", i, dtab[i], strlen(dtab[i]));
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

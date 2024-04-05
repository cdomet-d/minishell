/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:58:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/03 17:04:03 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing(t_input **input, t_env **env, char *line)
{
	t_input	*node;
	// int		fd;

	// fd = open("src/parsing/expansion/test/result_expand.txt", O_WRONLY);
	// if (fd == -1)
	// {
	// 	printf("shiiiit\n");
	// 	return ;
	// }
	node = NULL;
	if (tokenization(input, env, line))
		return ;
	if (input && *input)
	{
		node = *input;
		while (node)
		{
			if (node->tok != heredoc)
				if (check_for_dollar(node))
					// fd = expand(node, env, fd);
					if (expand(node, env))
						fatal_exit(input, errno, NULL);
			node = node->next;
		}
	}
	// close(fd);
	// remove_quote()
}

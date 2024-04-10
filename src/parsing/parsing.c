/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:58:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/09 16:38:02 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing(t_input **input, t_env **env, char *line)
{
	t_input	*node;

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
					if (expand(node, env))
						fatal_exit(input, errno, NULL);
			// else
				// check if delimiter is in quotes (single or double) or not
			node = node->next;
		}
	}
	//remove_quote()
	//find_builtin()
	if (cmd_path(input, env))
		return ;
}

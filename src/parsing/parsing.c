/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:58:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/10 17:51:21 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	search_for_expand(t_input **input, t_env **env)
{
	t_input	*node;

	node = NULL;
	node = *input;
	while (node)
	{
		if (node->tok != heredoc)
		{
			if (check_for_dollar(node))
			{
				node->data = expand(node->data, env);
				if (!node->data)
				{
					input_freelst(input);
					return (1);
				}
			}
		}
		// else
			// check if delimiter is in quotes (single or double) or not
		node = node->next;
	}
	return (0);
}

void	parsing(t_input **input, t_env **env, char *line)
{
	if (tokenization(input, env, line))
		return ;
	if (search_for_expand(input, env))
		return ;
	//remove_quote()
	//find_builtin()
	cmd_path(input, env);
}

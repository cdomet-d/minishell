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

int	search_for_expand(t_input **input, t_env **env, int rv)
{
	t_input	*node;
	char	**newtab;

	newtab = NULL;
	node = NULL;
	node = *input;
	while (node)
	{
		if (node->tok != heredoc)
		{
			if (check_for_dollar(node))
			{
				newtab = expand(node->data, env, rv);
				if (!newtab || !newtab[0])
				{
					free_dtab(newtab);
					input_freelst(input);
					return (1);
				}
				free_dtab(node->data);
				node->data = newtab;
			}
		}
		// else
			// check if delimiter is in quotes (single or double) or not
		node = node->next;
	}
	return (0);
}

void	parsing(t_input **input, t_env **env, char *line, int rv)
{
	if (tokenization(input, env, line))
		return ;
	if (search_for_expand(input, env, rv))
		return ;
	//remove_quote()
	//find_builtin()
	cmd_path(input, env);
}

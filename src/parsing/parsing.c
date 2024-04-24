/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:58:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/24 19:29:06 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	revert(t_input *node)
{
	int	i;
	int	j;

	i = 0;
	if (!node->data)
		return ;
	while (node->data[i])
	{
		j = 0;
		while (node->data[i][j])
		{
			if (node->data[i][j] < 0)
				node->data[i][j] *= -1;
			j++;
		}
		i++;
	}
}

int	search_expand(t_input *node, t_env **env, int rv)
{
	char	**newtab;
	int		i;

	newtab = NULL;
	i = -1;
	if (!node->data)
		return (0);
	while (node->data[++i])
		put_in_neg(node->data[i], '"', '\'');
	if (search_dollar(node->data))
	{
		newtab = expand_split(node->data, env, rv);
		if (!newtab)
			return (1);
		if (!newtab[0])
		{
			free_dtab(newtab);
			newtab = NULL;
		}
		free_dtab(node->data);
		node->data = newtab;
	}
	return (0);
}

int	search_quotes(t_input *node)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	if (!node->data)
		return (0);
	while (node->data[++i])
	{
		j = 0;
		while (node->data[i][j])
		{
			if (node->data[i][j] == '"' || node->data[i][j] == '\'')
			{
				temp = rm_quotes(node->data[i]);
				if (!temp)
					return (1);
				free(node->data[i]);
				node->data[i] = temp;
				break ;
			}
			j++;
		}
	}
	return (0);
}

void	parsing(t_input **input, t_env **env, char *line, int rv)
{
	t_input	*node;

	if (tokenization(input, env, line))
		return ;
	node = *input;
	while (node)
	{
		if (node->tok != heredoc)
		{
			if (search_expand(node, env, rv))
				return (input_freelst(input));
		}
		// else if (node->data[0][0] != '"' && node->data[0][0] != '\'')     //creer un tok heredocexpand ????
		// 	node->data[0][0] *= -1;
		if (search_quotes(node))
			return (input_freelst(input));
		revert(node);
		if (node->tok == command)
			find_builtin(node);
		if (node->tok == command)
			if (cmd_path(node, env))
				return (input_freelst(input));
		node = node->next;
	}
}

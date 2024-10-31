/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:58:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/31 14:19:59 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	revert(t_input *node)
{
	size_t	i;
	size_t	j;

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

static int	search_expand(t_input *node, t_env **env, int status)
{
	char		**newtab;
	ssize_t		i;

	newtab = NULL;
	i = -1;
	if (!node->data)
		return (0);
	while (node->data[++i])
		put_in_neg(node->data[i], '"', '\'');
	if (search_dollar(node->data))
	{
		newtab = expand_split(node->data, env, status);
		if (!newtab)
			return (1);
		if (!newtab[0])
		{
			free_darr(newtab);
			newtab = NULL;
		}
		free_darr(node->data);
		node->data = newtab;
	}
	return (0);
}

static int	check_delim(t_input *node)
{
	size_t	i;

	i = 0;
	if (node->tok != heredoc)
		return (0);
	while (node->data[0][i])
	{
		if (node->data[0][i] == '"' || node->data[0][i] == '\'')
			return (0);
		i++;
	}
	node->data[0][0] *= -1;
	return (1);
}

static void	init_status(int *status)
{
	*status = 1;
}

void	parsing(t_input **input, t_env **env, char *line, int *status)
{
	t_input	*node;
	int		delim;

	if (tokenization(input, env, line, status))
		return ;
	node = *input;
	while (node)
	{
		if (node->tok != heredoc)
			if (search_expand(node, env, *status))
				return (input_freelst(input), init_status(status));
		delim = check_delim(node);
		if (search_quotes(node))
			return (input_freelst(input), init_status(status));
		if (!delim)
			revert(node);
		if (node->tok == command)
			find_builtin(node);
		if (node->tok == command)
			if (cmd_path(node, env))
				return (input_freelst(input), init_status(status));
		node = node->next;
	}
}

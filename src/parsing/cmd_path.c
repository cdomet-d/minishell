/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:25:53 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/13 17:18:11 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*find_path(char *cmd, char *env)
{
	char		*path;
	size_t		letter;
	size_t		i;
	size_t		size;

	i = 0;
	path = NULL;
	while (env[i])
	{
		letter = path_len(env, &i);
		size = letter + ft_strlen(cmd);
		path = ft_calloc(sizeof(char), size + 2);
		if (!path)
			return (print_error(errno, "minishell: parsing"));
		ft_strlcpy(path, env + (i - letter), letter + 1);
		path[letter++] = '/';
		ft_strlcpy(path + letter, cmd, ft_strlen(cmd) + 1);
		if (check_path(&path))
			return (path);
		free(path);
		path = NULL;
		if (env[i])
			i++;
	}
	return (cmd);
}

static int	path_slash(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	put_path(t_input *input, t_env	*node)
{
	char	*path;

	path = NULL;
	path = find_path(input->data[0], node->env + 5);
	if (!path)
		return (1);
	if (!ft_strncmp(path, input->data[0], ft_strlen(input->data[0]) + 1))
		return (0);
	free(input->data[0]);
	input->data[0] = path;
	return (0);
}

int	cmd_path(t_input *input, t_env **env)
{
	t_env	*node;

	node = *env;
	if (!input->data || !input->data[0][0])
		return (0);
	if (path_slash(input->data[0]))
		return (0);
	while (node)
	{
		if (!ft_strncmp(node->env, "PATH=", 5))
		{
			if (node->env[5])
				return (put_path(input, node));
		}
		node = node->next;
	}
	return (0);
}

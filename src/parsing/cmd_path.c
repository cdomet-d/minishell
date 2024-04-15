/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:25:53 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/15 18:47:41 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	path_len(char *env, int *i)
{
	int	len;

	len = 0;
	while (env[*i] && env[*i] != ':')
	{
		*i += 1;
		len++;
	}
	return (len);
}

char	*find_path(char *cmd, char *env)
{
	char	*path;
	int		letter;
	int		i;
	int		size;

	i = 0;
	while (env[i])
	{
		letter = path_len(env, &i);
		size = letter + (int)ft_strlen(cmd);
		path = ft_calloc(sizeof(char), size + 2);
		if (!path)
			return (NULL);
		fill_word(path, env + (i - letter), letter);
		path[letter++] = '/';
		fill_word(path + letter, cmd, (int)ft_strlen(cmd));
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		if (env[i])
			i++;
	}
	return (cmd);
}

int	path_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	put_path(t_input *input, t_env	*node)
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

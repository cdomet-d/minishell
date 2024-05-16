/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:25:53 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/16 16:17:57 by csweetin         ###   ########.fr       */
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

static int	put_path(t_input *input, t_env	*node, int *status)
{
	char	*path;

	path = NULL;
	path = find_path(input->data[0], node->env + 5);
	if (!path)
		return (1);
	if (!ft_strncmp(path, input->data[0], ft_strlen(input->data[0]) + 1))
	{
		ft_putstr_fd(input->data[0], 2);
		ft_putendl_fd(": command not found", 2);
		*status = 127;
		free_dtab(input->data);
		input->data = NULL;
		return (0);
	}
	free(input->data[0]);
	input->data[0] = path;
	return (0);
}

static int	check_path_slash(t_input *input, int *status)
{
	struct stat	buf;
	char		*cmd;

	cmd = input->data[0];
	if (access(cmd, X_OK) == 0)
	{
		if (stat(cmd, &buf) == -1)
			return (print_error(errno, "minishell: parsing"), -1);
		if (S_ISDIR(buf.st_mode))
		{
			parsing_error("minishell: ", cmd, ": Is a directory");
			*status = 126;
			free_dtab(input->data);
			input->data = NULL;
		}
	}
	else
	{
		parsing_error("minishell: ", cmd, ": No such file or directory");
		*status = 127;
		free_dtab(input->data);
		input->data = NULL;
	}
	return (1);
}

static int	path_slash(t_input *input, int *status)
{
	char	*cmd;
	size_t	i;

	cmd = input->data[0];
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (check_path_slash(input, status));
		i++;
	}
	return (0);
}

int	cmd_path(t_input *input, t_env **env, int *status)
{
	t_env	*node;
	int		rv;

	node = *env;
	if (!input->data || !input->data[0][0])
		return (0);
	rv = path_slash(input, status);
	if (rv == 1)
		return (0);
	if (rv == -1)
		return (1);
	while (node)
	{
		if (!ft_strncmp(node->env, "PATH=", 5))
		{
			if (node->env[5])
				return (put_path(input, node, status));
		}
		node = node->next;
	}
	parsing_error("minishell: ", input->data[0], ": No such file or directory");
	*status = 127;
	free_dtab(input->data);
	input->data = NULL;
	return (0);
}

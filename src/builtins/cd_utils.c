/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:38:33 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/13 16:41:08 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_directory(char *var, char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
	{
		if (errno == ENOENT)
		{
			parsing_error("minishell: cd: ", var, ": No such file or directory");
			return (1);
		}
		if (errno == ENAMETOOLONG)
			return (0);
		return (print_error(errno, "minishell: exec"), 1);
	}
	if (S_ISDIR(buf.st_mode))
		return (0);
	else
	{
		parsing_error("minishell: cd: ", var, ": No such file or directory");
		return (1);
	}
	return (0);
}

static int	change_pwds(t_env **env, char *path, char *var)
{
	t_env	*node;
	char	*key;

	node = *env;
	while (node)
	{
		if (!ft_strncmp(node->env, var, ft_strlen(var)))
		{
			key = split_wsep(node->env, '=');
			if (!key)
				return (1);
			free(node->env);
			node->env = ft_strjoin(key, path);
			free(key);
			if (!node->env)
				return (1);
			return (0);
		}
		node = node->next;
	}
	return (0);
}

int	pwds(t_input *in, char *path)
{
	char	*temp;

	temp = find_var_env((in)->env, "PWD=");
	if (temp)
	{
		if (!find_var_env((in)->env, "OLDPWD="))
		{
			if (!exprt_inenv(&(in)->env, "OLDPWD="))
				return (1);
		}
		if (change_pwds(&(in)->env, temp, "OLDPWD="))
			return (1);
		if (change_pwds(&(in)->env, path, "PWD="))
			return (1);
	}
	else
	{
		temp = ft_strjoin("PWD=", path);
		if (!temp)
			return (1);
		if (!exprt_inenv(&(in)->env, temp))
			return (free(temp), 1);
		free(temp);
	}
	return (0);
}

char	*check_len(char	*path, t_env *env)
{
	int			i;
	char		*pwd;
	struct stat	buf;

	i = 0;
	if (ft_strlen(path) > PATH_MAX)
	{
		pwd = find_var_env(env, "PWD=");
		if (!pwd || !pwd[0])
			return (path);
		while (pwd[i] && path[i] && pwd[i] == path[i])
			i++;
		if (ft_strlen(path + (i + 1)) > PATH_MAX)
			return (print_error(0, "File name too long"));
		if (stat(path + (i + 1), &buf) == -1)
		{
			if (errno == ENOENT)
				return (path);
			else
				return (print_error(errno, "minishell: exec"));
		}
		else if (S_ISDIR(buf.st_mode))
			return (path + (i + 1));
	}
	return (path);
}

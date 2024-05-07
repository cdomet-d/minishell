/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:38:33 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/03 19:16:13 by csweetin         ###   ########.fr       */
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
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(var, 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		else
			print_error(errno, "stat ");
		return (1);
	}
	if (S_ISDIR(buf.st_mode))
		return (0);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (0);
}

int	change_pwds(t_env **env, char *path, char *var)
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
			if (!node->env)
				return (1);
			free(key);
			node->env = node->env;
			return (0);
		}
		node = node->next;
	}
	return (0);
}

int	pwds(t_input *in, char *path)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
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
		temp = getcwd(temp, 0);
		if (!temp)
			return (1);
		temp2 = ft_strjoin("PWD=", temp);
		free(temp);
		if (!temp2)
			return (1);
		if (!exprt_inenv(&(in)->env, temp2))
			return (1);
		free(temp2);
	}
	return (0);
}

char	*make_path(char *tab, char *path, char **temp)
{
	char	*tmp;

	free(*temp);
	*temp = NULL;
	*temp = ft_strdup(path);
	if (!*temp)
		return (print_error(errno, NULL), NULL);
	tmp = ft_strjoin(path, tab);
	free(path);
	if (!tmp)
		return (print_error(errno, NULL), NULL);
	path = tmp;
	tmp = ft_strjoin(path, "/");
	free(path);
	if (!tmp)
		return (print_error(errno, NULL), NULL);
	path = tmp;
	return (path);
}

char	*check_len(char	*path, t_env *env)
{
	int			i;
	char		*pwd;
	char		*tmp;
	struct stat	buf;

	i = 0;
	if (ft_strlen(path) > PATH_MAX)
	{
		pwd = find_var_env(env, "PWD=");
		if (!pwd)
			return (path);
		while (pwd[i] && path[i] && pwd[i] == path[i])
			i++;
		tmp = path + (i + 1);
		if (stat(tmp, &buf) == -1)
		{
			if (errno == ENOENT)
				return (path);
			else
				return (print_error(errno, "stat "));
		}
		else if (S_ISDIR(buf.st_mode))
			return (tmp);
	}
	return (path);
}

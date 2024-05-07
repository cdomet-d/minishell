/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:58:02 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/03 19:35:36 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*cd_path(t_input *in)
{
	char	*temp;
	char	*path;
	char	*str;

	if (in->data[1][0] == '/')
		path = ft_strdup(in->data[1]);
	else
	{
		str = find_var_env(in->env, "PWD=");
		if (!str)
		{
			path = ft_strdup(in->data[1]);
			// if (!path)
			// 	return (print_error(errno, NULL), NULL);
			// return (path);
		}
		else
		{
			temp = ft_strjoin(str, "/");
			if (!temp)
				return (NULL);
			path = ft_strjoin(temp, in->data[1]);
			free(temp);
		}
	}
	if (!path)
		return (print_error(errno, NULL), NULL);
	path = prep_path(in->data[1], path);
	if (!path)
		return (NULL);
	printf("cd_path : %s\n", path);
	return (path);
}

int	special_cases(t_input *in, char **path)
{
	if (!in->data[1])
	{
		*path = ft_strdup(find_var_env(in->env, "HOME="));
		if (!*path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), -1);
		return (1);
	}
	else if (in->data[1][0] == '-' && !in->data[1][1])
	{
		*path = ft_strdup(find_var_env(in->env, "OLDPWD="));
		if (!*path)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), -1);
		if (!*path[0])
			return (-1);
		return (1);
	}
	return (0);
}

int	cd(t_input *in)
{
	char	*path;
	char	*tmp;
	int		rv;

	path = NULL;
	if (ft_arrlen((in)->data) > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	rv = special_cases(in, &path);
	if (rv == -1)
		return (1);
	if (!rv)
	{
		path = cd_path(in);
		if (!path)
			return (1);
	}
	if (check_directory(in->data[1], path))
		return (free(path), 1);
	tmp = check_len(path, in->env);
	if (!tmp)
		return (free(path), 1);
	if (chdir(tmp) == -1)
		return (free(path), print_error(errno, "chdir "), 1);
	if (pwds(in, path))
		return (free(path), 1);
	free(path);
	return (0);
}

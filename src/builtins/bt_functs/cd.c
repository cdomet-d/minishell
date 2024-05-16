/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/13 18:04:50 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "exec.h"

char	*init_path(t_input *in)
{
	char	*path;
	char	*temp;
	char	*str;

	path = NULL;
	temp = NULL;
	str = NULL;
	str = find_var_env(in->env, "PWD=");
	if (!str || !str[0])
	{
		str = NULL;
		str = getcwd(str, 0);
		if (!str)
			return (NULL);
		temp = ft_strjoin(str, "/");
		free(str);
	}
	else
		temp = ft_strjoin(str, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, in->data[1]);
	free(temp);
	return (path);
}

char	*cd_path(t_input *in)
{
	char	*path;

	if (in->data[1][0] == '/')
		path = ft_strdup(in->data[1]);
	else
		path = init_path(in);
	if (!path)
		return (print_error(errno, "minishell: exec"));
	path = prep_path(in->data[1], path);
	if (!path)
		return (NULL);
	if (check_directory(in->data[1], path))
		return (free(path), NULL);
	return (path);
}

int	special_cases(t_input *in, char **path)
{
	if (!in->data[1])
	{
		*path = find_var_env(in->env, "HOME=");
		if (!*path || !*path[0])
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), -1);
		*path = ft_strdup(*path);
		if (!*path)
			return (print_error(errno, "minishell: exec"), -1);
		return (1);
	}
	else if (in->data[1][0] == '-' && !in->data[1][1])
	{
		*path = find_var_env(in->env, "OLDPWD=");
		if (!*path || !*path[0])
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), -1);
		*path = ft_strdup(*path);
		if (!*path)
			return (print_error(errno, "minishell: exec"), -1);
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
		return (print_error(0, "minishell: cd: too many arguments"), 1);
	rv = special_cases(in, &path);
	if (rv == -1)
		return (1);
	if (!rv)
	{
		path = cd_path(in);
		if (!path)
			return (1);
	}
	tmp = check_len(path, in->env);
	if (!tmp)
		return (free(path), 1);
	if (chdir(tmp) == -1)
		return (free(path), print_error(errno, "minishell: exec"), 1);
	if (pwds(in, path))
		return (free(path), print_error(errno, "minishell: exec"), 1);
	free(path);
	return (0);
}

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

char	*init_path(t_input *in)
{
	char	*path;
	char	*temp;
	char	*str;
	
	str = find_var_env(in->env, "PWD=");
	if (!str)
	{
		str = getcwd(str, 0);
		if (!str)
			return (print_error(errno, NULL));
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
		return (print_error(errno, NULL), NULL);
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
		return (free(path), print_error(errno, "chdir "), 1);
	if (pwds(in, path))
		return (free(path), 1);
	free(path);
	return (0);
}

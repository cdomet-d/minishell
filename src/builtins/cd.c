/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:58:02 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/03 17:58:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*canonical_form(char *var, char *path, char **tab)
{
	int		i;
	int		j;
	char	*temp;

	(void)var;
	i = -1;
	j = 1;
	temp = NULL;
	while (tab[++i])
	{
		if (!ft_strncmp(tab[i], "..", 3) && i > 0 && ft_strncmp(tab[i - j], ".", 2)
			&& ft_strncmp(tab[i - j], "..", 3))
		{
			// if (check_directory(var, path))
			// 	return (free(temp), free(path), NULL);
			free(path);
			path = ft_strdup(temp);
			if (!path)
				return (free(temp), NULL);
			int len = ft_strlen(tab[i - j]) + 1;
			temp = ft_substr(path, 0, ft_strlen(path) - len);
			j += 2;
		}
		else if (ft_strncmp(tab[i], ".", 2))
		{
			path = make_path(tab[i], path, &temp);
			if (!path)
				return (NULL);
		}
	}
	return (free(temp), path);
}

char	*prep_path(char *var, char *path)
{
	char	**tab;
	char	*temp;

	tab = ft_split(path, '/');
	free(path);
	path = NULL;
	if (!tab)
		return (NULL);
	temp = ft_strdup("/");
	if (!temp)
		return (free_dtab(tab), print_error(errno, NULL), NULL);
	path = canonical_form(var, temp, tab);
	free_dtab(tab);
	if (!path)
		return (NULL);
	return (path);
}

char	*cd_path(t_input *in)
{
	char	*temp;
	char	*path;

	temp = NULL;
	path = NULL;
	if (in->data[1][0] == '/')
		path = ft_strdup(in->data[1]);
	else
	{
		temp = ft_strjoin(find_var_env(in->env, "PWD="), "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, in->data[1]);
		free(temp);
		temp = NULL;
	}
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

int	len_tab(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

// char	*check_len(char	*path, t_input *in)
// {
// 	int		i;
// 	char	*pwd;
// 	char	*tmp;
// 	struct stat	buf;

// 		return (0);
// 	i = 0;
// 	if (ft_strlen(path) > PATH_MAX)
// 	{
// 		pwd = find_var_env(in->env, "PWD=");
// 		if (!pwd)
// 			return (path);
// 		while (pwd[i] && path[i] && pwd[i] == path[i])
// 			i++;
// 		tmp = ft_strjoin("./", path + i);
// 		free(path);
// 		if (!tmp)
// 			return (print_error(errno, NULL), NULL);
// 		stat(path, &buf);
// 		if (S_ISDIR(buf.st_mode))
// 			return (path);
// 		return (free(path), NULL);
// 	}
// 	return (path);
// }

int	cd(t_input *in)
{
	char	*path;
	int		rv;

	path = NULL;
	if (len_tab((in)->data) > 2)
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
	if (pwds(in, path))
		return (free(path), 1);
	// path = check_len(path, in->env);
	// if (!path)
		// return (1);
	if (chdir(path) == -1)
		return (free(path), print_error(errno, "chdir "), 1);
	free(path);
	return (0);
}

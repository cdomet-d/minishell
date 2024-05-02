//HEADER

#include "exec.h"

char	*canonical_form(char *var, char *path)
{
	int		i;
	char	**tab;
	char	*temp;

	i = 0;
	temp = NULL;
	tab = ft_split(path, '/');
	if (!tab)
		return (NULL);
	while (!ft_strncmp(tab[i], ".", 2) || !ft_strncmp(tab[i], "..", 3))
		i++;
	path = ft_strdup("/");
	if (!path)
		return (free_dtab(tab), print_error(errno, NULL), NULL);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], ".", 2))
			i++;
		else if (tab[i - 1] && ft_strncmp(tab[i - 1], ".", 2) && !ft_strncmp(tab[i], "..", 3)
			&& ft_strncmp(tab[i - 1], "..", 3))
		{
			if (check_directory(var, path))
				return (free_dtab(tab), free(path), NULL);
			path = temp;
			i += 1;
		}
		else if (tab[i])
		{
			temp = path;
			path = ft_strjoin(path, tab[i]);
			if (!path)
				return (print_error(errno, NULL), NULL);
			path = ft_strjoin(path, "/");
			if (!path)
				return (print_error(errno, NULL), NULL);
			i++;
		}
	}
	free_dtab(tab);
	return (path);
}

char	*cd_path(t_input *in)
{
	char	*temp;
	char	*path;

	temp = NULL;
	path = NULL;
	if (in->data[1][0] == '/')
	{
		path = ft_strdup(in->data[1]);
		if (!path)
			return (NULL);
	}
	else
	{
		temp = ft_strjoin(find_var_env(in->env, "PWD="), "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, in->data[1]);
		if (!path)
			return (free(temp), NULL);
		free(temp);
		temp = NULL;
	}
	if (!path)
		return (print_error(errno, NULL), NULL);
	path = canonical_form(in->data[1], path);
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
		if (!*path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), -1);
		return (1);
	}
	else if (in->data[1][0] == '-' && !in->data[1][1])
	{
		*path = find_var_env(in->env, "OLDPWD=");
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

int	cd(t_input *in)
{
	char	*path;
	int		rv;
	// char	str[PATH_MAX];

	path = NULL;
	if (len_tab((in)->data) > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	rv = special_cases(in, &path);
	if (rv != 0)
	{
		if (rv == -1)
			return (1);
		if (chdir(path) == -1)
			return (print_error(errno, NULL), 1);
		if (check_pwd(in, path))
			return (1);
		return (0);
	}
	path = cd_path(in);
	if (!path)
		return (1);
	if (chdir(path) == -1)
		return (free(path), print_error(errno, NULL), 1);
	if (check_pwd(in, path))
		return (free(path), 1);
	free(path);
	return (0);
}

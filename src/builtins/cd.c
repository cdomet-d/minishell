//HEADER

#include "exec.h"

char	*canonical_form(char *path)
{
	int		i;
	char	**tab;

	i = 0;
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
		if (ft_strncmp(tab[i], ".", 2) && ft_strncmp(tab[i], "..", 3) && tab[i + 1]
			&& !ft_strncmp(tab[i + 1], "..", 3))
		{
			if (check_directory(tab[i]))
				return (free_dtab(tab), free(path), NULL);
			i += 2;
		}
		path = ft_strjoin(path, tab[i]);
		if (!path)
			return (print_error(errno, NULL), NULL);
		path = ft_strjoin(path, "/");
		if (!path)
			return (print_error(errno, NULL), NULL);
		if (tab[i])
			i++;
	}
	printf("canon forme : %s\n", path);
	free_dtab(tab);
	return (path);
}

void	*cd_path(t_input *in)
{
	char	*temp;
	char	*path;

	temp = NULL;
	path = NULL;
	if (in->data[1][0] == '/' || in->data[1][0] == '.'
		|| (in->data[1][0] == '.' && in->data[1][1] == '.'))
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
		path = ft_strjoin(temp, path);
		if (!path)
			return (free(temp), NULL);
		free(temp);
		temp = NULL;
	}
	if (!path)
		return (print_error(errno, NULL), NULL);
	temp = canonical_form(path);
	if (!temp)
		return (free(path), NULL);
	free(path);
	path = temp;
	if (check_directory(path))
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

int	check_pwd(t_input **in, char *path)
{
	char	*temp;

	temp = NULL;
	temp = find_var_env((*in)->env, "PWD=");
	if (temp)
	{
		if (!find_var_env((*in)->env, "OLDPWD="))
		{
			if (!exprt_inenv(&(*in)->env, "OLDPWD="))
				return (1);
		}
		if (change_pwd(&(*in)->env, temp, "OLDPWD="))
			return (1);
		if (change_pwd(&(*in)->env, path, "PWD="))
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

int	cd(t_input **in)
{
	char	*path;
	int		rv;
	// char	str[PATH_MAX];

	path = NULL;
	if (len_tab((*in)->data) > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	rv = special_cases(*in, &path);
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
	path = cd_path(*in);
	if (!path)
		return (1);
	printf("path : %s\n", path);
	if (chdir(path) == -1)
		return (free(path), print_error(errno, NULL), 1);
	if (check_pwd(in, path))
		return (free(path), 1);
	free(path);
	return (0);
}

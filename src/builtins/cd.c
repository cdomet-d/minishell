//HEADER

#include "exec.h"

int	change_pwd(t_env **env, char *path, char *var)
{
	t_env	*node;
	char	*key;
	char	*newstr;

	node = *env;
	while (node)
	{
		if (!ft_strncmp(node->env, var, ft_strlen(var)))
		{
			key = split_wsep(node->env, '=');
			if (!key)
				return (1);
			newstr = ft_strjoin(key, path);
			if (!newstr)
				return (1);
			free(key);
			free(node->env);
			node->env = newstr;
			return (0);
		}
		node = node->next;
	}
	return (0);
}
// while (apath[i])
// {
// 	j = 0;
// 	if (apath[i] == '.')
// 	{
// 		if (i == 0)
// 		{
// 			if (apath[i + 1] == '/')
// 				j++;
// 			apath = ft_strdup(apath + j + 1);
// 		}
// 		else
// 		{
// 			temp = ft_substr(apath, 0, i);
// 			if (!temp)
// 				return (free(apath), NULL);
// 			j++;
// 			while (apath[i + j] && apath[i + j] == '/')
// 				j++;
// 			apath = ft_strjoin(temp, apath + (i + j));
// 			if (!apath)
// 				return (free(temp), NULL);
// 		}
// 	}
// 	if (apath[i])
// 		i++;
// }
// if (temp)
// 	free(temp);

char	*canonical_form(char *path)
{
	int		i;
	char	*temp;
	char	**tab;

	i = 0;
	temp = NULL;
	tab = ft_split(path, '/');
	if (!tab)
		return (NULL);
	while (!ft_strncmp(tab[i], ".", 2) || !ft_strncmp(tab[i], "..", 3))
		i++;
	path = ft_strdup("/");
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], ".", 2))
			i++;
		path = ft_strjoin(path, tab[i]);
	}
	printf("canon forme : %s\n", path);
	return (path);
}

void	*cd_path(t_input *in)
{
	char	*temp;
	char	*path;

	temp = NULL;

	if (in->data[1][0] == '/' || in->data[1][0] == '.'
		|| (in->data[1][0] == '.' && in->data[1][1] == '.'))
		path = ft_strdup(in->data[1]);
	else
	{
		temp = ft_strjoin(find_var_env(in->env, "PWD="), "/");
		//ft_strjoin("./", in->data[1]);
		path = ft_strjoin(temp, path);
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
	// temp = ft_strjoin(find_var_env(in->env, "PWD="), "/");
	// path = ft_strjoin(temp, path);
	// free(temp);
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
		return (1);
	}
	return (0);
}

int	cd(t_input *in)
{
	char	*path;
	char	*temp;
	int		len;
	int		rv;

	path = NULL;
	temp = NULL;
	len = 0;
	while (in->data[len])
		len++;
	if (len > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	rv = special_cases(in, &path);
	if (rv != 0)
	{
		if (rv == -1)
			return (1);
		if (chdir(path) == -1)
			return (print_error(errno, NULL), 1);
		return (0);
	}
	path = cd_path(in);
	if (!path)
		return (1);
	printf("path : %s\n", path);
	if (chdir(path) == -1)
		return (free(path), print_error(errno, NULL), 1);
	temp = ft_strdup(find_var_env(in->env, "PWD="));
	if (!temp)
		return (free(path), 1);
	change_pwd(&(in)->env, path, "PWD=");
	change_pwd(&(in)->env, temp, "OLDPWD=");
	free(temp);
	free(path);
	return (0);
}

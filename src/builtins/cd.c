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

char	*canonical_form(char *apath)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = NULL;
	while (apath[i])
	{
		j = 0;
		if (apath[i] == '.')
		{
			if (i == 0)
			{
				if (apath[i + 1] == '/')
					j++;
				apath = ft_strdup(apath + j + 1);
			}
			else
			{
				temp = ft_substr(apath, 0, i);
				if (!temp)
					return (free(apath), NULL);
				j++;
				while (apath[i + j] && apath[i + j] == '/')
					j++;
				apath = ft_strjoin(temp, apath + (i + j));
				if (!apath)
					return (free(temp), NULL);
			}
		}
		if (apath[i])
			i++;
	}
	if (temp)
		free(temp);
	printf("canon forme : %s\n", apath);
	return (apath);
}

int	cd_path(t_input *in, char **path, char **apath)
{
	char	*temp;

	temp = NULL;
	if (!in->data[1])
	{
		*path = find_var_env(in->env, "HOME=");
		if (!*path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	}
	else if (in->data[1][0] == '-' && !in->data[1][1])
	{
		*path = find_var_env(in->env, "OLDPWD=");
		if (!*path)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
	}
	else
	{
		if (in->data[1][0] == '/' || in->data[1][0] == '.'
			|| (in->data[1][0] == '.' && in->data[1][1] == '.'))
			*apath = ft_strdup(in->data[1]);
		else
			*apath = ft_strjoin("./", in->data[1]);
		if (!*apath)
			return (print_error(errno, NULL), 1);
		if (check_directory(*apath))
			return (free(*apath), 1);
		printf("cd_path 1: %s\n", *apath);
		temp = canonical_form(*apath);
		free(*apath);
		*apath = temp;
		printf("cd_path 2: %s\n", *apath);
		if (!*apath)
			return (1);
		temp = ft_strjoin(find_var_env(in->env, "PWD="), "/");
		*apath = ft_strjoin(temp, *apath);
		printf("cd_path 3: %s\n", *apath);
		*path = *apath;
		free(temp);
	}
	return (0);
}

int	cd(t_input *in)
{
	char	*path;
	char	*apath;
	char	*temp;
	int		len;

	path = NULL;
	apath = NULL;
	temp = NULL;
	len = 0;
	while (in->data[len])
		len++;
	if (len > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (cd_path(in, &path, &apath))
		return (1);
	printf("path : %s\n", path);
	if (chdir(path) == -1)
	{
		if (apath)
			free(apath);
		return (print_error(errno, NULL), 1);
	}
	temp = ft_strdup(find_var_env(in->env, "PWD="));
	if (!temp)
	{
		if (apath)
			free(apath);
		return (1);
	}
	change_pwd(&(in)->env, path, "PWD=");
	change_pwd(&(in)->env, temp, "OLDPWD=");
	free(temp);
	if (apath)
		free(apath);
	return (0);
}

//HEADER

#include "exec.h"

char	*find_var_env(t_env *env, char *var)
{
	while (env)
	{
		if (!ft_strncmp(env->env, var, ft_strlen(var)))
			return (env->env + ft_strlen(var));
		env = env->next;
	}
	return (NULL);
}

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

char	*check_directory(char *var)
{
	char		*path;
	struct stat	buf;

	path = ft_strjoin("./", var);
	if (!path)
		return (print_error(errno, NULL), NULL);
	stat(path, &buf);
	// if (stat(path, &buf) == -1)
	// {
	// 	free(path);
	// 	path = NULL;
	// 	return (print_error(errno, NULL), NULL);
	// }
	if (S_ISDIR(buf.st_mode))
		return (path);
	else
	{
		free(path);
		path = NULL;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (NULL);
	}
	return (path);
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
		if (apath[i])
			i++;
	}
	printf("%s\n", apath);
	if (temp)
		free(temp);
	return (apath);
}

int	cd_path(t_input *in, char **path, char **apath)
{
	(void)apath;
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
	else if (in->data[1][0] == '/')
	{
		*apath = ft_strdup(in->data[1]);
		*apath = canonical_form(*apath);
		*path = *apath;
	}
	else
	{
		*apath = check_directory(in->data[1]);
		if (!*apath)
			return (1);
		*apath = canonical_form(*apath);
		*path = *apath;
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

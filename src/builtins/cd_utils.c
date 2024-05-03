//HEADER

#include "exec.h"

int check_directory(char *var, char *path)
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

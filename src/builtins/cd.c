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

int	cd(t_input *in)
{
	char	*path;
	char	*temp;

	path = NULL;
	if (in->data[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2));
	if (!in->data[1])
	{
		path = find_var_env(in->env, "HOME=");
		if (!path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2));
		if (chdir(path) == -1)
			return (1);
	}
	else if (in->data[1][0] == '-' && !in->data[1][1])
	{
		path = find_var_env(in->env, "OLDPWD=");
		if (!path)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2));
		chdir(path);
	}
	temp = ft_strdup(find_var_env(in->env, "PWD="));
	if (!temp)
		return (1);
	change_pwd(&(in)->env, path, "PWD=");
	change_pwd(&(in)->env, temp, "OLDPWD=");
	free(temp);
	return (0);
}

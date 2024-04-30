//HEADER

#include "exec.h"

int check_directory(char *var)
{
	struct stat	buf;

	stat(var, &buf);
	// if (stat(path, &buf) == -1)
	// {
	// 	free(path);
	// 	path = NULL;
	// 	return (print_error(errno, NULL), NULL);
	// }
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

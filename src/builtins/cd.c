//HEADER

#include "exec.h"

char    *find_home(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->env, "HOME=", 5))
			return (env->env + 5);
		env = env->next;
	}
	return (NULL);
}

int cd(t_input *in)
{
	char    *home;

	if (!in->data[1])
	{
		home = find_home(in->env);
		if (!home)
			return (ft_putendl_fd("minishell : cd : HOME not set", STDERR_FILENO));
		chdir(home);
	}
	return (0);
}
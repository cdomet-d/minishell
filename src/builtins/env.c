//HEADER

#include "exec.h"

int	env(t_input *node)
{
	if (node->data[1])
	{
		if (ft_putstr_fd("env : too many arguments\n", 2) == -1)
			return (1);
		return (0);
	}
	while (node->env)
	{
		if (ft_putstr_fd(node->env->env, STDOUT_FILENO) == -1)
			return (1);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (1);
		node->env = node->env->next;
	}
	return (0);
}


// int main(int argc, char **argv, char **envp)
// {
// 	t_input	**input = NULL;
// 	t_env	**envi = NULL;

// 	(void)argc;
// 	create_env(input, envp, envi);
// 	create_input(input, envi, argv + 1, ms_env);
// 	env(*input);
// 	fatal_exit(input, EXIT_SUCCESS, "ras");
// 	return (0);
// }
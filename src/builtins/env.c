//HEADER

#include "exec.h"

int	env(t_input *node)
{
	if (node->data[1])
	{
		if (ft_putstr_fd("env : too many arguments\n", stderr) == -1)
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

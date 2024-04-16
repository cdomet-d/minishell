//HEADER

#include "exec.h"

int	env(t_input *node)
{
	if (node->data[1])
	{
		if (ft_putstr_fd("minishell : env : too many arguments\n", 2) == -1)
			return (1);
		return (0);
	}
	while (node->env)
	{
		if (ft_putstr_fd(node->env->env, 1) == -1)
			return (1);
		if (write(1, "\n", 1) == -1)
			return (1);
		node->env = node->env->next;
	}
	return (0);
}

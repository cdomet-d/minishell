//HEADER

#include "exec.h"

void	*env(t_input *node)
{
	if (node->data[1])
		return (print_error(E2BIG, "env (too many arguments)"));
	while (node->env)
	{
		if (ft_putendl_fd(node->env->env, STDOUT_FILENO) == -1)
			return (print_error(errno, "env (writing to STDOUT"));
		node->env = node->env->next;
	}
	return ((int *)true);
}

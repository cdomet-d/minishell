/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:57:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/03 17:57:42 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*env(t_input *in)
{
	t_env	*env;

	env = in->env;
	if (in->data[1])
		return (print_error(E2BIG, "env (too many arguments)"));
	while (env)
	{
		if (ft_putendl_fd(env->env, STDOUT_FILENO) == -1)
			return (print_error(errno, "env (writing to STDOUT"));
		env = env->next;
	}
	return ((int *)true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:57:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/23 15:10:40 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	env(t_input *in)
{
	t_env	*env;

	env = in->env;
	if (in->data[1])
		return (verror("minishell: ", "env: ", strerror(E2BIG)));
	while (env)
	{
		if (g_sig == SIGPIPE || ft_putendl_fd(env->env, STDOUT_FILENO) == -1)
			return (verror("minishell: ", "env: ", strerror(errno)));
		env = env->next;
	}
	return (0);
}

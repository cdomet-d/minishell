/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:57:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/08 18:34:09 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_input *in)
{
	t_env	*env;

	env = in->env;
	if (in->data[1])
		return (parsing_error("minishell: ", "env: ", strerror(E2BIG)));
	while (env)
	{
		if (ft_putendl_fd(env->env, STDOUT_FILENO) == -1)
			return (parsing_error("minishell: ", "env: ", strerror(errno)));
		env = env->next;
	}
	return (0);
}

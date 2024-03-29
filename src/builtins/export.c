/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/29 15:08:45 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*exprt_inenv(t_env **env, char *data)
{
	t_env	*new;

	new = env_newnode(data);
	if (!new)
		return (NULL);
	env_addback(env, new);
	return (new);
}

void	*export(t_env *env, char *var)
{
	char	*key;
	t_env	*head;

	if (!env || !var)
		return (print_error(errno, "NULL param in export"));
	key = split_wsep(var, '=');
	if (!key)
		return (print_error(errno, NULL));
	head = env;
	while (env)
	{
		if (ft_strncmp(key, env->env, ft_strlen(key)) == 0)
		{
			free(env->env);
			free(key);
			return (env->env = ft_strdup(var));
		}
		env = env->next;
	}
	free(key);
	env = head;
	return (exprt_inenv(&env, var));
}

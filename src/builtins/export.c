/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/28 17:30:13 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	exprt_inenv(t_env **env, char *data)
{
	t_env	*new;

	new = env_newnode(data);
	if (!new)
		return (print_error(errno, "could not initialize environnement"));
	env_addback(env, new);
}

void	export(t_env *env, char *var)
{
	char	*key;
	t_env	*head;

	if (!env || !var)
		return ;
	key = split_wsep(var, '=');
	if (!key)
		return (print_error(errno, "failure in export"));
	head = env;
	while (env)
	{
		if (ft_strncmp(key, env->env, ft_strlen(key)) == 0)
		{
			free(env->env);
			env->env = ft_strdup(var);
			return (free(key));
		}
		env = env->next;
	}
	free(key);
	env = head;
	exprt_inenv(&env, var);
}

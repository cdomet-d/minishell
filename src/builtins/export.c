/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/22 15:29:49 by cdomet-d         ###   ########lyon.fr   */
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

void	*export(t_input **in, char *var)
{
	char	*key;
	t_env	*head;
	
	fprintf(stderr, "%.20s\n", "-- export ---------------------------------");
	if (!(*in)->env || !var)
		return (print_error(errno, "NULL param in export"));
	key = split_wsep(var, '=');
	if (!key)
		return (print_error(errno, NULL));
	head = (*in)->env;
	while ((*in)->env)
	{
		if (ft_strncmp(key, (*in)->env->env, ft_strlen(key)) == 0)
		{
			free((*in)->env->env);
			free(key);
			(*in)->env->env = ft_strdup(var);
			(*in)->env = head;
			return ((*env));
		}
		(*in)->env = (*in)->env->next;
	}
	free(key);
	(*in)->env = head;
	exprt_inenv(&(*in)->env, var);
	return (in);
}

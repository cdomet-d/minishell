/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/22 19:22:45 by csweetin         ###   ########.fr       */
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

int	check_arg(char *var)
{
	int	i;

	i = 0;
	if (var[0] != '_' || !ft_isalpha(var[0]))
	{
		print_error(errno, "minishell: export: '");
		print_error(errno, var);
		print_error(errno, "': not a valid identifier");
		return (1);
	}
	while (var[i])
	{
		if (var[i] != '_' || !ft_isalnum(var[i]))
		{
			print_error(errno, "minishell: export: '");
			print_error(errno, var);
			print_error(errno, "': not a valid identifier");
			return (1);
		}
		i++;
	}
	return (0);
}

void	*export(t_env *env, char *var)
{
	char	*key;
	t_env	*head;

	if (!env || !var)
		return (print_error(errno, "NULL param in export"));
	if (check_arg(var))
		return (NULL);
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

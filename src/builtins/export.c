/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
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

// int	check_arg(char *var)
// {
// 	int	i;

// 	i = 0;
// 	if (var[0] != '_' || !ft_isalpha(var[0]))
// 	{
// 		print_error(errno, "minishell: export: '");
// 		print_error(errno, var);
// 		print_error(errno, "': not a valid identifier");
// 		return (1);
// 	}
// 	while (var[i])
// 	{
// 		if (var[i] != '_' || !ft_isalnum(var[i]))
// 		{
// 			print_error(errno, "minishell: export: '");
// 			print_error(errno, var);
// 			print_error(errno, "': not a valid identifier");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void	*export(t_input **in, char *var)
{
	char	*key;
	t_env	*head;
	
	fprintf(stderr, "%.20s\n", "-- export ---------------------------------");
	if (!(*in)->env || !var)
		return (print_error(errno, "NULL param in export"));
	// if (check_arg(var))
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

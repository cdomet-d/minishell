/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/17 14:55:11 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_arg(char *var)
{
	size_t	i;

	i = 0;
	if (var[0] != '_' && !ft_isalpha(var[0]))
	{
		parsing_error("minishell: export: '", var, "': not a valid identifier");
		return (1);
	}
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
		{
			parsing_error("minishell: export: '", var, \
			"': not a valid identifier");
			return (1);
		}
		i++;
	}
	if (!var[i])
		return (1);
	return (0);
}

int	change_var(t_input **in, char *var)
{
	char	*key;

	key = split_wsep(var, '=');
	if (!key)
		return (-1);
	while ((*in)->env)
	{
		if (ft_strncmp(key, (*in)->env->env, ft_strlen(key)) == 0)
		{
			free((*in)->env->env);
			free(key);
			(*in)->env->env = ft_strdup(var);
			if (!(*in)->env->env)
				return (-1);
			return (1);
		}
		(*in)->env = (*in)->env->next;
	}
	free(key);
	return (0);
}

int	exec_export(t_input **in, t_env *head)
{
	size_t	i;
	int		rv;
	bool	status;

	status = true;
	i = 0;
	while ((*in)->data[++i])
	{
		if (!check_arg((*in)->data[i]))
		{
			rv = change_var(in, (*in)->data[i]);
			if (rv == -1)
				return (1);
			(*in)->env = head;
			if (!rv)
				if (!exprt_inenv(&(*in)->env, (*in)->data[i]))
					return (0);
		}
		else
			status = false;
	}
	if (status == false)
		return (1);
	return (0);
}

int	export(t_input **in)
{
	t_env	*head;

	head = (*in)->env;
	if ((*in)->env && !(*in)->data[1])
		if (sort_env((*in)->env) == 1)
			return (1);
	return (exec_export(in, head));
}
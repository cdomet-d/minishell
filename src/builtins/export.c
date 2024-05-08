/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/07 17:27:08 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_arg(char *var)
{
	int	i;

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

void	*export(t_input **in)
{
	int		i;
	int		rv;
	t_env	*head;

	i = 1;
	head = (*in)->env;
	if ((*in)->env && !(*in)->data[i])
		sort_env((*in)->env);
	while ((*in)->data[i])
	{
		(*in)->status = check_arg((*in)->data[i]);
		if (!(*in)->status)
		{
			rv = change_var(in, (*in)->data[i]);
			if (rv == -1)
				return (print_error(errno, NULL));
			(*in)->env = head;
			if (!rv)
				if (!exprt_inenv(&(*in)->env, (*in)->data[i]))
					return (NULL);
		}
		else if ((*in)->status == 1)
			return (NULL);
		i++;
	}
	return (in);
}

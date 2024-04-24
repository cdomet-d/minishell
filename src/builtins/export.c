/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/24 18:27:40 by csweetin         ###   ########.fr       */
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
	if (var[0] != '_' && !ft_isalpha(var[0]))
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
		{
			ft_putstr_fd("minishell: export: '", STDERR_FILENO);
			ft_putstr_fd(var, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*export(t_input **in, char **var)
{
	char	*key;
	t_env	*head;
	int		i;
	bool	n;

	i = 1;
	n = false;
	if ((*in)->env && !var[i])
		return (NULL);//sort_env((*in)->env));
	head = (*in)->env;
	while (var[i])
	{
		if (!check_arg(var[i]))
		{
			key = split_wsep(var[i], '=');
			if (!key)
				return (print_error(errno, NULL));
			while ((*in)->env)
			{
				if (ft_strncmp(key, (*in)->env->env, ft_strlen(key)) == 0)
				{
					n = true;
					free((*in)->env->env);
					free(key);
					(*in)->env->env = ft_strdup(var[i]);
					break ;
				}
				(*in)->env = (*in)->env->next;
			}
			free(key);
			(*in)->env = head;
			if (n == false)
				exprt_inenv(&(*in)->env, var[i]);
		}
		i++;
	}
	return (in);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:00:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/13 16:43:26 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_env	*env_rmone(t_env **sup, t_env **head)
{
	t_env	*tmp;

	if (!(*sup))
		return (print_error(errno, "minishell: exec"));
	tmp = (*sup);
	if (!tmp->prev)
	{
		(*sup) = (*sup)->next;
		(*sup)->prev = NULL;
		head = sup;
	}
	else if (!tmp->next)
		(*sup)->prev->next = NULL;
	else
	{
		(*sup)->prev->next = (*sup)->next;
		(*sup)->next->prev = (*sup)->prev;
	}
	sup = head;
	free(tmp->env);
	free(tmp);
	return (*sup);
}

t_env	**unset(t_env **env, char **key)
{
	t_env	*head;
	size_t	i;

	if (!env || !(*env) || !key)
		return (env);
	head = (*env);
	i = 1;
	while ((*env) && key[i])
	{
		if (key[i] && ft_strncmp((*env)->env, key[i], ft_strlen(key[i])) == 0)
		{
			head = env_rmone(env, &head);
			(*env) = head;
			i++;
		}
		if ((*env))
			(*env) = (*env)->next;
		else
			(*env) = head;
	}
	(*env) = head;
	return (env);
	//return value : 130: No such file or directory
}

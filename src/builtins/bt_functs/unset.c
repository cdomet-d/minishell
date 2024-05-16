/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/16 20:37:03 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	size_t	env_len(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

static t_env	*env_rmone(t_env **sup, t_env **head)
{
	t_env	*tmp;

	if (!(*sup))
		return (print_error(errno, "minishell: exec"));
	tmp = (*sup);
	if (!tmp->prev)
	{
		(*sup) = (*sup)->next;
		if (env_len(tmp) > 1)
			(*sup)->prev = NULL;
		head = sup;
	}
	else if ((*sup) && !tmp->next)
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

int	unset(t_input	**in)
{
	t_env	*head;
	bool	missing;
	size_t	i;

	if (!in || !(*in) || !(*in)->env || ((*in)->data && !(*in)->data[1]))
		return (1);
	head = (*in)->env;
	missing = false;
	i = 1;
	while ((*in)->env && (*in)->data[i])
	{
		if ((*in)->data && (*in)->data[i] && ft_strncmp((*in)->env->env, (*in)->data[i], \
			ft_strlen((*in)->data[i])) == 0)
		{
			head = env_rmone(&(*in)->env, &head);
			(*in)->env = head;
			i++;
		}
		else
			missing = true;
		if ((*in)->env && (*in)->env->next)
			(*in)->env = (*in)->env->next;
		else
		{
			(*in)->env = head;
			if (missing)
				break;
		}		
	}
	(*in)->env = head;
	return (0);
}

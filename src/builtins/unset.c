/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/13 18:05:05 by cdomet-d         ###   ########lyon.fr   */
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

int	unset(t_input	**in)
{
	t_env	*head;
	size_t	i;

	fprintf(stderr, "%.20s\n", "-- unset ----------------------");
	if (!in || !(*in) || !(*in)->env || ((*in)->data && !(*in)->data[1]))
		return (1);
	head = (*in)->env;
	i = 1;
	while ((*in)->env && (*in)->data[i])
	{
		if ((*in)->data[i] && ft_strncmp((*in)->env->env, (*in)->data[i], ft_strlen((*in)->data[i])) == 0)
		{
			head = env_rmone(&(*in)->env, &head);
			(*in)->env = head;
			i++;
		}
		if ((*in)->env)
			(*in)->env = (*in)->env->next;
		else
			(*in)->env = head;
	}
	(*in)->env = head;
	return (0);
}

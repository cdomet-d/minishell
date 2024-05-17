/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/17 13:57:19 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "exec.h"

static char	*comp_keys(char *to_find, char *key)
{
	size_t	i;
	
	if (!to_find || !key)
		return (NULL);
	i = 0;
	while(to_find[i] && i <ft_strlen(key))
	{
		if (to_find[i] != key[i])
			return (NULL);
		i++;
	}
	if (to_find[i] != '=')
			return (NULL);
	return (to_find);
}

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
	size_t	i;

	if (!in || !(*in) || !(*in)->env || ((*in)->data && !(*in)->data[1]))
		return (1);
	head = (*in)->env;
	i = 1;
	while ((*in)->env && (*in)->data[i])
	{
		if ((*in)->data && (*in)->data[i] && comp_keys((*in)->env->env, \
			(*in)->data[i]))
		{
			head = env_rmone(&(*in)->env, &head);
			(*in)->env = head;
			i++;
		}
		if ((*in)->env)
			(*in)->env = (*in)->env->next;
	}
	(*in)->env = head;
	return (0);
}

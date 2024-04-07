/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:01:23 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/07 22:30:26 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*split_wsep(char *str, char sep)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!str || !sep)
		return (NULL);
	while (str[i] && str[i] != sep)
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	res = ft_substr(str, 0, i + 1);
	if (!res)
		return (NULL);
	return (res);
}

void	*env_rmone(t_env **sup, t_env *head)
{
	t_env	*tmp;

	if (!(*sup))
		return (print_error(errno, "minishell: invalid data in env_rmone"));
	tmp = (*sup);
	if (!tmp->prev)
	{
		(*sup)->next->prev = NULL;
		(*sup) = (*sup)->next;
	}
	else if (!tmp->next)
	{
		(*sup)->prev->next = NULL;
		(*sup) = head;
	}
	else
	{
		(*sup)->prev->next = (*sup)->next;
		(*sup)->next->prev = (*sup)->prev;
		(*sup) = head;
	}
	free(tmp->env);
	free(tmp);
	return (*sup);
}

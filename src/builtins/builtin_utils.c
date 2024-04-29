/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:01:23 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/29 17:31:56 by cdomet-d         ###   ########lyon.fr   */
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

t_env	**env_rmone(t_env **sup, t_env *head)
{
	t_env	*tmp;
	
	if (!(*sup))
		return (print_error(errno, "minishell: invalid data in env_rmone"));
	tmp = (*sup);
	if (!tmp->prev)
	{
		fprintf(stderr, "\033[0;36m%.20s\033[0m\n", "-- first node ------------------");
		(*sup) = (*sup)->next;
		(*sup)->prev = NULL;
		head = (*sup);
	}
	else if (!tmp->next)
	{
		fprintf(stderr, "\033[0;36m%.20s\033[0m\n", "-- last node ------------------");
		(*sup)->prev->next = NULL;
	}
	else
	{
		fprintf(stderr, "\033[0;36m%.20s\033[0m\n", "-- any other node ------------------");
		(*sup)->prev->next = (*sup)->next;
		(*sup)->next->prev = (*sup)->prev;
	}
	(*sup) = head;
	free(tmp->env);
	free(tmp);
	return (sup);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:00:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/28 16:05:42 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	unset(t_env **env, char *key)
{
	t_env	*head;
	size_t	i;

	if (!env || !(*env) || !key)
		return ;
	head = (*env);
	i = 0;
	while ((*env))
	{
		if (ft_strncmp(key, (*env)->env, ft_strlen(key)) == 0 && \
			(*env)->env[ft_strlen(key)] == '=')
		{
			env_rmone(env, head);
			return ;
		}
		(*env) = (*env)->next;
		i++;
	}
	(*env) = head;
	printf("minishell: %s: not a valid identifier\n", key);
	//return value : 130: No such file or directory
}

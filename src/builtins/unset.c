/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:00:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/29 16:56:22 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_env	**unset(t_env **env, char **key)
{
	t_env	*head;
	size_t	i;

	if (!env || !(*env) || !key)
		return (env);
	head = (*env);
	i = 1;
	printf("key[1] : %s\n", key[i]);
	while ((*env))
	{
		if (key[i] && ft_strncmp((*env)->env, key[i], ft_strlen(key[i])) == 0)
		{
			printf("removing : key %s\n", key[i]);
			head = *env_rmone(env, head);
			// print_env_for(*env);
			i++;
		}
		(*env) = (*env)->next;
	}
	(*env) = head;
	print_env_for(*env);
	// (*env) = head;
	return (env);
	// printf("minishell: %s: not a valid identifier\n\n", key);
	//return value : 130: No such file or directory
}

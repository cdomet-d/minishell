/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:45:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/26 15:46:26 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	create_env(char **envp, t_env **env)
{
	int		i;
	t_env	*new;

	i = 0;
	new = NULL;
	while (envp[i])
	{
		new = env_newnode(envp[i]);
		if (!new)
			free_env(*env, EXIT_FAILURE, NULL);
		env_addback(env, new);
		i++;
	}
}

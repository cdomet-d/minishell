/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:33:32 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 20:05:16 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// all exit are to be replaced with free_all funct.
void	env_addback(t_env **env, t_env *node)
{
	t_env	*ptr;

	if (!node || !env)
		return ;
	if (!*env)
		*env = node;
	else
	{
		ptr = *env;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
		node->prev = ptr;
	}
}

t_env	*env_newnode(char *data)
{
	t_env	*node;

	node = malloc(1 * sizeof(t_env));
	if (!node)
		exit(EXIT_FAILURE);
	node->env = ft_strdup(data);
	if (!node->env)
		exit(EXIT_FAILURE);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	env_freelst(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		free(env->env);
		tmp = env->next;
		free(env);
		env = tmp;
	}
	env = NULL;
}
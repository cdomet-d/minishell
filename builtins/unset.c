/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:00:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/27 18:06:33 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	unset(t_env **env, char *key)
{
	t_env	*head;

	if (!env || !(*env) || !key)
		return ;
	head = (*env);
	while ((*env))
	{
		if (ft_strncmp(key, (*env)->env, ft_strlen(key)) == 0)
		{
			env_rmone(env);
			return;
		}
		(*env) = (*env)->next;
	}
	(*env) = head;
	print_error(errno, "minishell: ");
	print_error(errno, key);
	print_error(errno, ": not a valid identifier");
	//return value : 130: No such file or directory
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = NULL;
	if (argc == 2)
	{
		init_env(envp, &env);
		unset(&env, argv[1]);
		print_env_for(env);
		env_freelst(env);
		exit(EXIT_SUCCESS);
	}
	else
		print_error(0, "Expected one argument");
	exit(EXIT_FAILURE);
}
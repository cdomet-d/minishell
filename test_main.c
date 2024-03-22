/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:50:37 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 17:59:41 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_env	*envnew;
	t_env	*env;
	size_t	i;

	i = 0;
	env = NULL;
	if (argc < 2)
		return (EXIT_FAILURE);
	while (argv[i])
	{
		envnew = env_newnode(NULL, argv[i]);
		env_addback(&env, envnew);
		i++;
	}
	print_env_for(env);
	print_env_back(env);
	env_freelst(env);
}

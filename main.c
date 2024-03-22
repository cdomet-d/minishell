/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:50:37 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 12:25:06 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	main(int argc, char *argv[])
{
	t_env	*new;
	t_env	*env;
	size_t	i;

	env = NULL;
	i = 1;
	if (argc < 2)
		return (EXIT_FAILURE);
	while (argv[i])
	{
		new = env_create_node(NULL, argv[i]);
		env = env_add_back(&env, new);
		i++;
	}
	print_env_for(env);
	print_env_back(env);
}

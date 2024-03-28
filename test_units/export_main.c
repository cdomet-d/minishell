/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:58:53 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/28 17:30:13 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = NULL;
	if (argc == 2)
	{
		init_env(envp, &env);
		export(env, argv[1]);
		print_env_for(env);
		env_freelst(env);
		exit(EXIT_SUCCESS);
	}
	else
		print_error(0, "Expected one argument");
	exit(EXIT_FAILURE);
}

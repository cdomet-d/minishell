/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:50:37 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/25 12:43:48 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*envnew;
	t_env	*env;
	t_input	*inew;
	t_input	*input;
	size_t	i;

	i = 0;
	env = NULL;
	input = NULL;
	if (argc < 2)
		return (EXIT_FAILURE);
	while (envp[i])
	{
		envnew = env_newnode(envp[i]);
		if (!envnew)
			free_env(env, errno, NULL);
		env_addback(&env, envnew);
		i++;
	}
	i = 1;
	while (argv[i])
	{
		inew = input_newnode(ft_split(argv[i], ' '), command, env);
		if (!inew)
			free_all(&input, errno, NULL);
		input_addback(&input, inew);
		i++;
	}
	print_in_for(input);
	free_all(&input, EXIT_SUCCESS, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:50:37 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/25 18:17:48 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;
	t_input	*input;

	env = NULL;
	input = NULL;
	if (argc < 2)
		return (EXIT_FAILURE);
	init_env(envp, &env);
	init_input(argv, &input, env);
	count_pipes(input, NULL);
	print_in_for(input);
	free_all(&input, EXIT_SUCCESS, NULL);
}

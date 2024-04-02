/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/02 18:30:26 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_input	*input;

	(void)argv;
	line = NULL;
	env = NULL;
	input = NULL;
	if (argc != 1)
		fatal_exit(NULL, EXIT_FAILURE, "minishell: too many arguments");
	create_env(&input, envp, &env);
	while (1)
	{
		line = readline("Minishell > ");
		if (line)
		{
			if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
				mh_exit(line, input, env);
			add_history(line);
			parsing(&input, &env, line);
			exec_cmd(input);
			free(line);
		}
		input_freelst(&input);
	}
	env_freelst(env);
	return (0);
}

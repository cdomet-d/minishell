/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/09 17:06:54 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "exec.h"
#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_input	*input;

	if (argc != 1)
		fatal_exit(NULL, EXIT_FAILURE, "minishell: too many arguments");
	(void)argv;
	init_all(&line, envp, &env, &input);
	while (1)
	{
		line = readline("Minishell > ");
		if (line)
			process_line(line, input, env);
	}
	env_freelst(env);
	return (0);
}

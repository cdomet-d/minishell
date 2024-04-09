/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/29 17:23:04 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
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
		line = readline("Minishell > "); //besoin de proteger readline ???
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0 && line[0])
			mh_exit(line, input, env);
		parsing(&input, &env, line, 1);
		// exec_cmd(input);
		print_in_for(input);
		free(line);
		input_freelst(&input);
	}
	return (0);
}

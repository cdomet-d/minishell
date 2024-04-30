/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:04:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/30 17:58:25 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

int	g_sig;

static void	init_all(char **str, char **envp, t_env **env, t_input **input)
{
	*str = NULL;
	*env = NULL;
	*input = NULL;
	create_env(input, envp, env);
}

static t_env	*process_line(char *line, t_input *input, t_env **env)
{
	if (ft_strncmp(line, "exit", 5) == 0)
		mh_exit(line, input, env);
	add_history(line);
	parsing(&input, env, line, 0);
	if (input)
	{
		exec_cmd(input);
		*env = input->env;
	}
	input_freelst(&input);
	return (*env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_input	*input;

	if (argc != 1)
		fatal_exit(NULL, EXIT_FAILURE, "minishell: too many arguments");
	(void)argv;
	init_all(&line, envp, &env, &input);
	rl_event_hook = get_nonull;
	signal(SIGINT, sighandler);
	while (1)
	{
		sigend();
		line = readline("Minishell > ");
		if (line && g_sig != SIGINT)
		{
			env = process_line(line, input, &env);
		}
		if (line)
			free(line);
	}
	return (0);
}

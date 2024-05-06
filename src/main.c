/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:04:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/03 14:56:11 by cdomet-d         ###   ########lyon.fr   */
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

static t_env	*process_line(char *line, t_input *input, t_env **env, int *status)
{
	if (ft_strncmp(line, "exit", 5) == 0)
		mh_exit(line, input, env);
	add_history(line);
	parsing(&input, env, line, *status);
	if (input)
	{
		input->status = *status;
		exec_cmd(input);
		*env = input->env;
		*status = input->status;
	}
	input_freelst(&input);
	return (*env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_input	*input;
	int		status;

	if (argc != 1)
		fatal_exit(NULL, EXIT_FAILURE, "minishell: too many arguments");
	status = 0;
	(void)argv;
	init_all(&line, envp, &env, &input);
	rl_event_hook = get_nonull;
	signal(SIGINT, sighandler);
	while (1)
	{
		sigend();
		line = readline("Minishell > ");
		if (line && g_sig != SIGINT)
			env = process_line(line, input, &env, &status);
		if (line)
			free(line);
	}
	return (127);
}

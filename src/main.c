/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:04:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/22 18:28:55 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	g_sig;

static void	init_all(char **str, char **envp, t_env **env, t_input **input)
{
	*str = NULL;
	*env = NULL;
	*input = NULL;
	create_env(input, envp, env);
}

static t_env	*process_line(char **line, t_input *in, t_env **env, int *stat)
{
	if (*line[0])
		add_history(*line);
	parsing(&in, env, *line, stat);
	if (in)
	{
		in->status = *stat;
		// in->head = in;
		if (!count_pipes(in) && in->tok == ms_exit)
		{
			*stat = mh_exit(line, in);
			input_freelst(&in);
			return (*env);
		}
		exec_cmd(in);
		*env = in->env;
		*stat = in->status;
	}
	input_freelst(&in);
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
	(void)argv;
	status = 0;
	init_all(&line, envp, &env, &input);
	siglisten();
	while (1)
	{
		sigend();
		line = readline("MinisHell$ ");
		if (!send_eof(line))
			exit_no_input(&env, line, status);
		if (line && g_sig != SIGINT)
			env = process_line(&line, input, &env, &status);
		if (g_sig == SIGINT)
			status = 128 + g_sig;
		if (line)
			free(line);
	}
	exit (status);
}


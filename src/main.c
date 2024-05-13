/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:04:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/13 12:12:40 by cdomet-d         ###   ########lyon.fr   */
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
	// if (ft_strncmp(line, "exit", 5) == 0)
	// {
	// 	env_freelst(env);
	// 	print_error(0, "exit");
	// 	exit(*status);
	// }
	add_history(line);
	parsing(&input, env, line, status);
	if (input)
	{
		input->status = *status;
		if (input->tok == ms_exit)
			mh_exit(line, input);
		exec_cmd(input);
		*env = input->env;
		*status = input->status;
	}
	else
		*status = errno;
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
	(void)argv;
	status = 0;
	init_all(&line, envp, &env, &input);
	siglisten();
	while (1)
	{
		sigend();
		line = readline("Minishell > ");
		if (!send_eof(line))
			exit_no_input(&env, line, status);
		if (line && g_sig != SIGINT)
			env = process_line(line, input, &env, &status);
		if (line)
			free(line);
	}
	exit (status);
}

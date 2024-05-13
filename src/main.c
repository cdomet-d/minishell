/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:04:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/13 17:13:19 by csweetin         ###   ########.fr       */
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

static t_env	*process_line(char *line, t_input *in, t_env **env, int *stat)
{
	add_history(line);
	parsing(&in, env, line, stat);
	if (in)
	{
		in->status = *stat;
		if (in->tok == ms_exit)
			mh_exit(line, in);
		exec_cmd(in);
		*env = in->env;
		*stat = in->status;
	}
	else
	{
		if (*stat != 2)
			*stat = errno;
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

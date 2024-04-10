/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:08:34 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/10 18:11:29 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_all(char **str, char **envp, t_env **env, t_input **input)
{
	*str = NULL;
	*env = NULL;
	*input = NULL;
	create_env(input, envp, env);
}

void	process_line(char *line, t_input *input, t_env *env)
{
	if (ft_strncmp(line, "exit", 5) == 0)
		mh_exit(line, input, env);
	add_history(line);
	parsing(&input, &env, line);
	print_in_for(input);
	if (input)
		exec_cmd(input);
	input_freelst(&input);
	free(line);
}

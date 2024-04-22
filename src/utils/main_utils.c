/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:08:34 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/22 15:06:56 by cdomet-d         ###   ########lyon.fr   */
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
	parsing(&input, &env, line, 0);
	if (input)
		exec_cmd(input);
	input_freelst(&input);
	free(line);
}

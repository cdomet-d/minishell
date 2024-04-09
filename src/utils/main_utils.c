/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:08:34 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/07 22:27:13 by jauseff          ###   ########lyon.fr   */
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
	if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		mh_exit(line, input, env);
	add_history(line);
	parsing(&input, &env, line);
	if (input)
		exec_cmd(input);
	input_freelst(&input);
	free(line);
}

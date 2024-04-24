/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:54:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/23 17:15:34 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	mh_exit(char *line, t_input *in, t_env **env)
{
	fprintf(stderr, "%.20s\n", "-- exit ---------------------------------");
	rl_clear_history();
	if (line)
		free(line);
	fprintf(stderr, "%p\n", env);
	if (env && *env)
		env_freelst(env);
	fatal_exit(&in, 0, NULL);
	// return value to be determined with signals
}

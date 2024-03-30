/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:54:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/29 18:57:17 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	mh_exit(char *line, t_input *in, t_env *env)
{
	rl_clear_history();
	if (line)
		free(line);
	if (env)
		env_freelst(env);
	fatal_exit(&in, 0, NULL);
	// return value to be determined with signals
}

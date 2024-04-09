/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 23:32:19 by jauseff           #+#    #+#             */
/*   Updated: 2024/04/09 17:56:56 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exe_failure(t_fd *fd, t_input *in, char **arenv)
{
	fprintf(stderr, "%.20s\n", "-- execfail ---------------------------------");
	close_tmpin(in, fd);
	free_dtab(arenv);
	env_freelst(in->env);
	input_freelst(&in);
	exit(EXIT_FAILURE);
}

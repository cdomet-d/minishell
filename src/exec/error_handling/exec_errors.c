/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 23:32:19 by jauseff           #+#    #+#             */
/*   Updated: 2024/05/15 16:26:15 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*killchild(t_fd *fd, t_input *in)
{
	int		e_stat;
	t_input	*last;

	fprintf(stderr,  "%.20s\n", "-- killchild ------------------");
	last = get_last_node(in);
	if (builtin_true(last))
		e_stat = in->status;
	else
		e_stat = 1;
	close_pfd(fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (in && in->env)
		env_freelst(&in->env);
	input_freelst(&in);
	exit(e_stat);
}

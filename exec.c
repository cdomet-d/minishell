/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/26 16:11:25 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_cmd(t_input *in)
{
	t_op	op;
	// t_fd	fd;

	check_redirs(in, &op);
	print_ops(op);
	print_env_for(in->env);
	// while (op.pip >= 0)
	// {
	// 	if (pipe(fd.ffd) == -1)
	// }
}

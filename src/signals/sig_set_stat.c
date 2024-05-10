/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_set_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:13:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/10 19:15:52 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_status(t_input *in, int e_stat)
{
	struct stat	infos;
	t_input		*last;

	last = get_last_node(in);
	if (builtin_true(last))
		in->status = 1;
	if (WIFEXITED(e_stat))
	{
		if (e_stat != 256)
			return ;
		if (access(last->data[0], X_OK) != -1)
		{
			if (last->data[1] && access(last->data[1], X_OK) == -1)
				in->status = 1;
			else if (stat(last->data[0], &infos) != -1)
				if (S_ISDIR(infos.st_mode))
					in->status = 126;
		}
		else if (access(last->data[0], X_OK) == -1)
			in->status = 127;
	}
	else if (WIFSIGNALED(e_stat))
		in->status = 128 + WTERMSIG(e_stat);
	return ;
}

void	set_status(t_input *in, int e_stat)
{
	t_input		*last;
	
	printf ("%d\n", WEXITSTATUS(e_stat));
	last = get_last_node(in);
	if (builtin_true(last))
		in->status = 1;
	if (WIFEXITED(e_stat))
		in->status = WEXITSTATUS(e_stat);
	else if (WIFSIGNALED(e_stat))
		in->status = 128 + WTERMSIG(e_stat);
	return ;
}

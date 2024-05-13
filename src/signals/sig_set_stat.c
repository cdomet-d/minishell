/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_set_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:13:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/13 17:58:31 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	set_error(t_input *in, t_input *last)
{
	struct stat	infos;

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

void	set_status(t_input *in, int e_stat)
{
	t_input		*last;

	last = get_last_node(in);
	if (here_true(last))
	{
		if (in->status == 130)
			return ;
		else
			last = find_prev_tok(in, command);
	}
	if (WIFEXITED(e_stat))
	{
		if (builtin_true(last) && e_stat != 0)
		{	
			in->status = 1;
			return ;
		}
		set_error(in, last);
	}
	if (WIFSIGNALED(e_stat))
		in->status = 128 + WTERMSIG(e_stat);
	return ;
}

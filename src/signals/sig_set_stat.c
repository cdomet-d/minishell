/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_set_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:13:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/23 15:13:36 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	set_error(t_input *in, t_input *last, int e_stat)
{
	struct stat	infos;

	in->status = WEXITSTATUS(e_stat);
	if (last->data && last->data[0] && access(last->data[0], X_OK) != -1)
	{
		if (last->data[1] && access(last->data[1], X_OK) == -1)
			in->status = WEXITSTATUS(e_stat);
		else if (stat(last->data[0], &infos) != -1)
			if (S_ISDIR(infos.st_mode))
				in->status = 126;
	}
	else if (last->data && last->data[0] && access(last->data[0], X_OK) == -1)
		in->status = 127;
}

void	set_status(t_input *in, int e_stat)
{
	t_input		*last;

	last = get_last_executable(in);
	if (WEXITSTATUS(e_stat) == 0 && !WTERMSIG(e_stat))
	{
		in->status = WEXITSTATUS(e_stat);
		return ;
	}
	if (here_true(last))
		last = find_prev_tok(in, command);
	if (WIFEXITED(e_stat))
	{
		if (builtin_true(last) && e_stat != 0)
		{
			in->status = WEXITSTATUS(e_stat);
			return ;
		}
		if (last)
			set_error(in, last, e_stat);
	}
	else if (WIFSIGNALED(e_stat))
	{
		if (WTERMSIG(e_stat) == SIGQUIT)
			printf("Core dumped\n");
		in->status = 128 + WTERMSIG(e_stat);
	}
	return ;
}

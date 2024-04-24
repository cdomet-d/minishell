/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:58 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/24 14:09:39 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_tok	builtin_true(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp && tmp != pip)
	{
		if (tmp->tok == ms_cd)
			return (ms_cd);
		if (tmp->tok == ms_echo)
			return (ms_echo);
		if (tmp->tok == ms_pwd)
			return (ms_pwd);
		if (tmp->tok == ms_env)
			return (ms_env);
		if (tmp->tok == ms_exit)
			return (ms_exit);
		if (tmp->tok == ms_export)
			return (ms_export);
		if (tmp->tok == ms_unset)
			return (ms_unset);
		tmp = tmp->next;
	}
	return (false);
}

void	exec_exit_inpipe(t_fd *fd, t_input *in, t_input *tmp)
{
	if (builtin_true(tmp) == ms_exit)
	{
		print_fds(fd);
		if (count_pipes(in))
		{
			close_pfd(fd);
			if (fd->tmpin != -1)
				if (close(fd->tmpin) == -1)
					print_error(errno, "close_cmd (tmpin)");
		}
		mh_exit(NULL, in, &in->env);
	}
}

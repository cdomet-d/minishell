/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/31 14:19:59 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*ft_execve(t_input *in)
{
	char	**arenv;
	t_input	*tmp;

	tmp = find_tok(in, command, false);
	if (!tmp->data)
		return (NULL);
	arenv = NULL;
	if (in->env)
	{
		arenv = arenvlst(tmp->env);
		if (!arenv)
			return (NULL);
	}
	if (tmp->data[0] && access(tmp->data[0], X_OK) != -1 && \
		path_slash(tmp->data[0]))
		execve(tmp->data[0], tmp->data, arenv);
	if (arenv)
		free_darr(arenv);
	in->status = 1;
	display_exec_error(tmp);
	return (NULL);
}

static void	*redir_cmd(t_input *in, t_fd *fd)
{
	t_input	*tmp;

	tmp = in;
	if (fd->pnb != 0)
		if (!pip_redir(tmp, fd))
			return (NULL);
	if (!redir_all_in_pipe(fd, tmp))
		return (NULL);
	if (op_true(tmp, command))
		ft_execve(tmp);
	if (builtin_true(tmp))
		exec_builtin(&tmp);
	in->status = tmp->status;
	return (NULL);
}

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;

	init_exec(in, &tmp, &fd);
	create_hdocs(&fd, in);
	while (tmp)
	{
		if (fd.pid != 0 && !count_pipes(in) && builtin_true(tmp))
			tmp = handle_bt_nopipe(&fd, tmp);
		if (tmp && fd.pid != 0)
			if (!create_child(&fd))
				return (NULL);
		if (tmp && fd.pid == 0)
		{
			if (!redir_cmd(tmp, &fd))
				in->status = tmp->status;
			killchild(&fd, in);
		}
		if (fd.pnb != 0)
			save_pipin(&fd);
		tmp = find_next_pipe(tmp, &fd);
	}
	close_and_wait(in, &fd);
	sigend();
	return ((int *)true);
}

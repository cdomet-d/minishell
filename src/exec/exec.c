/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/21 19:35:46 by cdomet-d         ###   ########lyon.fr   */
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
	arenv = arenvlst(tmp->env);
	if (!arenv)
		return (verror \
		("minishell: ", tmp->data[0], ": no such file or directory"), NULL);
	if (tmp->data[0] && access(tmp->data[0], X_OK) != -1)
		execve(tmp->data[0], tmp->data, arenv);
	if (arenv)
		free_dtab(arenv);
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
	if (op_true(tmp, outredir) || op_true(tmp, append))
		if (!out_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, inredir))
		if (!in_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, heredoc))
		if (!here_redir(fd, tmp))
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
	return ((int *)true);
}

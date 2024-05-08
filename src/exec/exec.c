/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/07 17:17:16 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*ft_execve(t_input *in)
{
	char	**arenv;
	t_input	*tmp;

	// fprintf(stderr, "\033[0;36m%.20s\033[0m\n", "-- execve ------------------");
	tmp = find_tok(in, command, false);
	if (!tmp->data)
		return (print_error(0, "ft_execve (data is null)"));
	arenv = NULL;
	arenv = arenvlst(tmp->env);
	if (!arenv)
		(print_error(errno, "ft_execve (memissue in arenv)"));
	if (tmp->data[0] && access(tmp->data[0], X_OK) != -1)
		execve(tmp->data[0], tmp->data, arenv);
	if (arenv)
		free_dtab(arenv);
	return (print_error(errno, tmp->data[0]));
}

static void	*redir_cmd(t_input *in, t_fd *fd)
{
	t_input	*tmp;

	tmp = in;
	if (fd->pnb != 0)
		if (!pip_redir(tmp, fd))
			return (NULL);
	if (op_true(tmp, inredir))
		if (!in_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, outredir))
		if (!out_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, heredoc))
		if (!here_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, append))
		if (!app_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, command))
		if (!ft_execve(tmp))
			return (NULL);
	if (builtin_true(tmp))
		if (!exec_builtin(&tmp))
			return (NULL);
	return (NULL);
}

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;

	tmp = in;
	in->status = 0;
	init_fds(&fd, in);
	if (here_true(in))
		if (!create_hdocs(&fd, in))
			return (print_error(errno, "exec_cmd (creating heredoc)"));
	while (tmp)
	{
		if (fd.pid != 0 && !count_pipes(in) && builtin_true(tmp))
			handle_bt_nopipe(&fd, in, tmp);
		if (fd.pid != 0)
			if (!create_child(tmp, &fd))
				return (print_error(errno, "exec_cmd (create_child)"));
		if (tmp && fd.pid == 0)
			if (!redir_cmd(tmp, &fd))
				exe_failure(&fd, in);
		if (fd.pnb != 0)
			save_pipin(&fd);
		tmp = find_next_pipe(tmp, &fd);
	}
	close_and_wait(in, &fd);
	return ((int *)true);
}

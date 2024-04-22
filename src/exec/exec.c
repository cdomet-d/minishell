/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/22 11:05:17 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*ft_execve(t_input *in, t_fd fd)
{
	char	**arenv;
	t_input	*tmp;

	(void)fd;
	// fprintf(stderr, "\033[0;32m%.20s\033[0m\n", "-- execve ---------------------------------");
	tmp = in;
	if (builtin_true(tmp))
	{
		exec_builtin(tmp);
		return ((int *)true);
	}
	else
		tmp = find_tok(in, command, false);
	if (!tmp->data)
		return (print_error(0, "ft_execve (data is null)"));
	arenv = NULL;
	arenv = arenvlst(tmp->env);
	if (!arenv)
		(print_error(errno, "ft_execve (memissue in arenv)"));
	if (tmp->data[0] && access(tmp->data[0], X_OK) != -1)
		execve(tmp->data[0], tmp->data, arenv);
	print_error(errno, tmp->data[0]);
	if (arenv)
		free_dtab(arenv);
	return ((int *)false);
}

static void	*redir_exec(t_input *in, t_fd *fd)
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
	if (op_true(tmp, append))
		if (!app_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, command) || builtin_true(tmp))
		ft_execve(tmp, *fd);
	return ((int *)false);
}

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;

	init_fds(&fd);
	tmp = in;
	fd.pnb = count_pipes(tmp);
	pmin(tmp, NULL);
	if (op_true(in, heredoc))
		create_hdocs(&fd, in);
	while (tmp)
	{
		if (fd.pid != 0)
			if (!create_child(&fd))
				return (print_error(errno, "exec_cmd (create_child)"));
		if (tmp && fd.pid == 0)
			if (!redir_exec(tmp, &fd))
				exe_failure(&fd, in, NULL);
		if (fd.pnb != 0)
			save_pipin(&fd);
		tmp = find_next_pipe(tmp, &fd);
	}
	if (count_pipes(in))
		close_pipe_read(&fd);
	wait_for_children();
	return ((int *)true);
}

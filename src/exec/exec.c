/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/23 17:45:15 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*ft_execve(t_input *in)
{
	char	**arenv;
	t_input	*tmp;

	fprintf(stderr, "\033[0;36m%.20s\033[0m\n", "-- execve ------------------");
	tmp = find_tok(in, command, false);
	pmin(tmp, "execve");
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

static void	*redir_builtins(t_input *tmp, t_fd *fd)
{
	if (fd->pnb != 0)
		if (!pip_redir(tmp, fd))
			return (print_error(errno, "redir_builtins 1"));
	if (op_true(tmp, inredir))
		if (!in_redir(fd, tmp))
			return (print_error(errno, "redir_builtins 2"));
	if (op_true(tmp, outredir))
		if (!out_redir(fd, tmp))
			return (print_error(errno, "redir_builtins 3"));
	if (op_true(tmp, append))
		if (!app_redir(fd, tmp))
			return (print_error(errno, "redir_builtins 4"));
	return ((int *)true);
}

static void	*redir_cmd(t_input *in, t_fd *fd)
{
	t_input	*tmp;

	tmp = in;
	pmin(tmp, "in redir_cmd");
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
	if (op_true(tmp, command))
		ft_execve(tmp);
	return ((int *)false);
}

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;
	int		tmpstdin;
	int		tmpstdout;

	init_fds(&fd);
	fd.pnb = count_pipes(in);
	tmp = in;
	pmin(tmp, NULL);
	if (op_true(in, heredoc))
		create_hdocs(&fd, in);
	while (tmp)
	{
		if (fd.pid != 0)
		{
			if (builtin_true(tmp) && builtin_true(tmp) != ms_exit)
			{
				if (fd.pnb != 0)
				{
					fprintf(stderr, "%.20s\n", "-- pipe (bins) --------------");
					if (pipe(fd.pfd) == -1)
						return (print_error(errno, "builtins (piping)"));
				}
				fprintf(stderr, "%.20s\n", "-- builtin ----------------------");
				tmpstdin = dup(STDIN_FILENO);
				tmpstdout = dup(STDOUT_FILENO);
				if (!redir_builtins(tmp, &fd))
					return (print_error(errno, "exec_cmd (redirections)"));
				exec_builtin(&tmp);
				if (fd.pnb != 0)
					save_pipin(&fd);
				if (dup2(tmpstdin, STDIN_FILENO) == -1)
					return (print_error(errno, "redir_b (reopening STDIN"));
				if (dup2(tmpstdout, STDOUT_FILENO) == -1)
					return (print_error(errno, "redir_b (reopening STDOUT"));
				close(tmpstdin);
				close(tmpstdout);
				tmp = find_next_pipe(tmp, &fd);
			}
		}
		if (fd.pid != 0)
			if (!create_child(tmp, &fd))
				return (print_error(errno, "exec_cmd (create_child)"));
		if (tmp && fd.pid == 0)
		{
			if (builtin_true(tmp) == ms_exit)
			{
				print_fds(&fd);
				if (count_pipes(in))
				{
					close_pfd(&fd);
					if (fd.tmpin != -1)
						if (close(fd.tmpin) == -1)
							print_error(errno, "close_cmd (tmpin)");
				}
				mh_exit(NULL, in, &in->env);
			}
			if (!redir_cmd(tmp, &fd))
				exe_failure(in);
		}
		if (fd.pnb != 0)
			save_pipin(&fd);
		tmp = find_next_pipe(tmp, &fd);
	}
	if (count_pipes(in))
		close_pipe_read(&fd);
	wait_for_children();
	return ((int *)true);
}

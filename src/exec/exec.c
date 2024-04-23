/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/23 14:06:04 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*ft_execve(t_input *in, t_fd fd)
{
	char	**arenv;
	t_input	*tmp;

	(void)fd;
	fprintf(stderr, "\033[0;36m%.20s\033[0m\n", "-- execve ---------------------------------");
	fprintf(stderr, "\033[0;36m%.20s || %d\033[0m\n", "-- execve  ---------------------------------", fd.pid);
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

static void *redir_builtins(t_input *tmp, t_fd *fd)
{


	pmin(tmp, NULL);
	if (fd->pnb != 0)
		if (!pip_redir(tmp, fd, builtin_true(tmp)))
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
	if (fd->pnb != 0)
		if (!pip_redir(tmp, fd, command))
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
		ft_execve(tmp, *fd);
	return ((int *)false);
}

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;
	int	tmpstdin;
	int	tmpstdout;

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
			if (builtin_true(tmp))
			{
				if (fd.pnb != 0)
				{
					fprintf(stderr, "%.20s\n", "-- pipe (bins) ------------------");
					if (pipe(fd.pfd) == -1)
						return (print_error(errno, "builtins (piping)"));
				}
				fprintf(stderr, "%.20s\n", "-- builtin ---------------------------------");
				tmpstdin = STDIN_FILENO;
				tmpstdout = STDOUT_FILENO;
				if (!redir_builtins(tmp, &fd))
					return (print_error(errno, "exec_cmd (redirections)"));
				exec_builtin(&tmp);
				if (fd.pnb != 0)
					save_pipin(&fd);
				if (dup2(tmpstdin, STDIN_FILENO) == -1)
					return (print_error(errno, "redir_builtins (reopening STDIN"));
				// close(tmpstdin);
				if (dup2(tmpstdout, STDOUT_FILENO) == -1)
					return (print_error(errno, "redir_builtins (reopening STDOUT"));
				// close(tmpstdout);
				fprintf(stderr, "%.20s\n", "-- increment ---------------------------------");
				tmp = find_next_pipe(tmp, &fd);
			}
		}
		if (fd.pid != 0)
			if (!create_child(tmp, &fd))
				return (print_error(errno, "exec_cmd (create_child)"));
		if (tmp && fd.pid == 0)
			if (!redir_cmd(tmp, &fd))
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

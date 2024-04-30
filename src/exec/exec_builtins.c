/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:18:24 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/30 15:13:23 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtin(t_input **in)
{
	t_input	*tmp;

	// fprintf(stderr, "%.20s\n", "-- exec_bt ----------------------");
	tmp = (*in);
	if (builtin_true(tmp) == ms_cd)
		cd(tmp);
	if (builtin_true(tmp) == ms_echo)
		echo(tmp->data);
	else if (builtin_true(tmp) == ms_pwd)
		pwd(tmp->data);
	else if (builtin_true(tmp) == ms_env)
		env(tmp);
	else if (builtin_true(tmp) == ms_export)
		export(&tmp);
	else if (builtin_true(tmp) == ms_unset)
		tmp->env = *unset(&tmp->env, tmp->data);
}

void	*redir_builtins(t_fd *fd, t_input *tmp)
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
	exec_builtin(&tmp);
	return ((int *)true);
}

void	*handle_bt_nopipe(t_fd *fd, t_input	*in, t_input *tmp)
{
	int		tmpstdin;
	int		tmpstdout;

	(void)in;
	// fprintf(stderr, "%.20s\n", "-- handle_bt --------------");
	tmpstdin = dup(STDIN_FILENO);
	tmpstdout = dup(STDOUT_FILENO);
	if (!redir_builtins(fd, tmp))
		return (print_error(errno, "exec_cmd (redirections)"));
	reset_stds(tmpstdin, tmpstdout);
	tmp = find_next_pipe(tmp, fd);
	return ((int *)true);
}

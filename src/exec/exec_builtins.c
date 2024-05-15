/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:18:24 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/15 15:27:51 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*exec_builtin(t_input **in)
{
	t_input	*tmp;

	// fprintf(stderr,  "%.20s\n", "-- exec_bt ----------------------");
	tmp = builtin_true(*in);
	if (tmp->tok == ms_cd)
		(*in)->status = cd(tmp);
	if (tmp->tok == ms_echo)
		(*in)->status = echo(tmp->data);
	if (tmp->tok == ms_pwd)
		(*in)->status = pwd(tmp->env);
	if (tmp->tok == ms_env)
		(*in)->status = env(tmp);
	if (tmp->tok == ms_export)
		(*in)->status = export(&tmp);
	if (tmp->tok == ms_unset)
		(*in)->status = unset(&tmp);
	if ((*in)->status == 1)
		return (NULL);
	return ((int *)true);
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

void	*handle_bt_nopipe(t_fd *fd, t_input *tmp)
{
	int		tmpstdin;
	int		tmpstdout;

	// fprintf(stderr,  "%.20s\n", "-- handle bt_no_pipe ----------------------");
	tmpstdin = dup(STDIN_FILENO);
	tmpstdout = dup(STDOUT_FILENO);
	if (!redir_builtins(fd, tmp))
		return (print_error(errno, "exec_cmd (redirections)"));
	reset_stds(tmpstdin, tmpstdout);
	tmp = find_next_pipe(tmp, fd);
	return ((t_input *)tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:18:24 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/21 16:42:33 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*exec_builtin(t_input **in)
{
	t_input	*tmp;

	tmp = builtin_true(*in);
	(*in)->status = 0;
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
			return (NULL);
	if (op_true(tmp, outredir) || op_true(tmp, append))
		if (!out_redir(fd, tmp))
			return (NULL);
	if (op_true(tmp, inredir))
		if (!in_redir(fd, tmp))
			return (NULL);
	exec_builtin(&tmp);
	return ((int *)true);
}

void	*handle_bt_nopipe(t_fd *fd, t_input *tmp)
{
	int		tmpstdin;
	int		tmpstdout;

	tmpstdin = dup(STDIN_FILENO);
	tmpstdout = dup(STDOUT_FILENO);
	if (!redir_builtins(fd, tmp))
		return (NULL);
	reset_stds(tmpstdin, tmpstdout);
	tmp = find_next_pipe(tmp, fd);
	return ((t_input *)tmp);
}

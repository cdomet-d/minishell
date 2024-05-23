/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:18:24 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/22 18:34:08 by cdomet-d         ###   ########lyon.fr   */
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
	if (tmp->tok == ms_exit)
		(*in)->status = mh_exit(NULL, tmp);
	if ((*in)->status == 1)
		return (NULL);
	return ((int *)true);
}

void	*handle_bt_nopipe(t_fd *fd, t_input *tmp)
{
	int		tmpstdin;
	int		tmpstdout;

	tmpstdin = dup(STDIN_FILENO);
	tmpstdout = dup(STDOUT_FILENO);
	if (!redir_all_in_pipe(fd, tmp))
		return (reset_stds(tmpstdin, tmpstdout), NULL);
	exec_builtin(&tmp);
	reset_stds(tmpstdin, tmpstdout);
	tmp = find_next_pipe(tmp, fd);
	return ((t_input *)tmp);
}

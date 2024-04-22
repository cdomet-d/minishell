/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:18:24 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/22 17:43:49 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int builtin_true(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp && tmp != pip)
	{
		if (tmp->tok == ms_cd)
			return (ms_cd);
		if (tmp->tok == ms_echo)
			return (ms_echo);
		if (tmp->tok == ms_pwd)
			return (ms_pwd);
		if (tmp->tok == ms_env)
			return(ms_env);
		if (tmp->tok == ms_exit)
			return (ms_exit);
		if (tmp->tok == ms_export)
			return (ms_export);
		if (tmp->tok == ms_unset)
			return (ms_unset);
		tmp = tmp->next;
	}
	return (false);
}

void exec_builtin(t_input **in)
{
	t_input	*tmp;

	tmp = (*in);
	// if (builtin_true(tmp) == ms_cd)
		// return (ms_cd);
	if (builtin_true(tmp) == ms_echo)
		echo(tmp->data);
	if (builtin_true(tmp) == ms_pwd)
		pwd(tmp->data);
	if (builtin_true(tmp) == ms_env)
		env(tmp);
	if (builtin_true(tmp) == ms_exit)
		mh_exit(NULL, tmp, tmp->env);
	if (builtin_true(tmp) == ms_export)
		export(&tmp, tmp->data[1]);
	if (builtin_true(tmp) == ms_unset)
		unset(&(*in)->env, tmp->data[1]);
}

// void builtin_redirs(t_input *tmp, t_fd *fd)
// {
// 	int	tmpstdin;
// 	int	tmpstdout;
	
// 	tmpstdin = STDIN_FILENO;
// 	tmpstdout = STDOUT_FILENO;
// }

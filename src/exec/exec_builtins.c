/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:18:24 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/23 17:46:01 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_tok builtin_true(t_input *in)
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
	// 	return (ms_cd);
	if (builtin_true(tmp) == ms_echo)
		echo(tmp->data);
	else if (builtin_true(tmp) == ms_pwd)
		pwd(tmp->data);
	else if (builtin_true(tmp) == ms_env)
			env(tmp);
	else if (builtin_true(tmp) == ms_export)
		export(&tmp, tmp->data[1]);
	else if (builtin_true(tmp) == ms_unset)
		unset(&(*in)->env, tmp->data[1]);
}

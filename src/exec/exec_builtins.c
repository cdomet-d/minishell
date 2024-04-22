/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:18:24 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/22 11:01:48 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int builtin_true(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp && tmp->tok != pip)
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

void exec_builtin(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	if (tmp->tok == ms_cd)
		// return (ms_cd);
	if (tmp->tok == ms_echo)
	{
		printf("%d\n", tmp->tok);
		pmin(tmp, "in echo");
		echo(tmp->data);
	}
	if (tmp->tok == ms_pwd)
		pwd(tmp->data);
	if (tmp->tok == ms_env)
		env(tmp);
	if (tmp->tok == ms_exit)
		mh_exit(NULL, tmp, tmp->env);
	if (tmp->tok == ms_export)
		export(tmp->env, tmp->data[1]);
	if (tmp->tok == ms_unset)
		unset(&tmp->env, tmp->data[1]);
}
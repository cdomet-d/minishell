/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:18:24 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/23 12:38:49 by cdomet-d         ###   ########lyon.fr   */
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
	{	
		fprintf(stderr, "%.20s\n", "-- echo ---------------------------------");
		echo(tmp->data);
	}
	if (builtin_true(tmp) == ms_pwd)
	{
		fprintf(stderr, "%.20s\n", "-- pwd ---------------------------------");
		pwd(tmp->data);
	}
	if (builtin_true(tmp) == ms_env)
	{
		fprintf(stderr, "%.20s\n", "-- env ---------------------------------");
		env(tmp);
	}
	if (builtin_true(tmp) == ms_exit)
	{
		fprintf(stderr, "%.20s\n", "-- exit ---------------------------------");
		mh_exit(NULL, tmp, tmp->env);
	}
	if (builtin_true(tmp) == ms_export)
	{
		fprintf(stderr, "%.20s\n", "-- exit ---------------------------------");
		export(&tmp, tmp->data[1]);
	}
	if (builtin_true(tmp) == ms_unset)
	{
		fprintf(stderr, "%.20s\n", "-- exit ---------------------------------");
		unset(&(*in)->env, tmp->data[1]);
	}
	fprintf(stderr, "%.20s\n", "-- end exec_builtins ---------------------------------");
}



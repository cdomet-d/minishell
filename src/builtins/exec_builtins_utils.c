/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:09:58 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/21 16:16:57 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_input	*builtin_true(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	if (tmp && tmp->tok == pip)
		tmp = tmp->next;
	while (tmp && tmp->tok != pip)
	{
		if (tmp->tok == ms_cd)
			return (tmp);
		if (tmp->tok == ms_echo)
			return (tmp);
		if (tmp->tok == ms_pwd)
			return (tmp);
		if (tmp->tok == ms_env)
			return (tmp);
		if (tmp->tok == ms_exit)
			return (tmp);
		if (tmp->tok == ms_export)
			return (tmp);
		if (tmp->tok == ms_unset)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

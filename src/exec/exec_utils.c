/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:27:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/02 17:38:08 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	pipe_true(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp)
	{
		if (tmp->tok == pip)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	init_fd(t_fd *fd)
{
	fd->pfd[R] = 0;
	fd->pfd[W] = 0;
	fd->ffd = 0;
	fd->pid = -1;
	fd ->tmpin = 0;
}

char	**arenvlst(t_env	*env)
{
	char	**arenv;
	size_t	i;
	size_t	len;
	t_env	*tmp;

	tmp = env;
	arenv = NULL;
	len = env_len(env);
	i = 0;
	arenv = malloc(sizeof(char *) * (len + 1));
	if (!arenv)
		return (print_error(errno, NULL));
	arenv[len] = 0;
	while (tmp)
	{
		arenv[i] = ft_strdup(tmp->env);
		if (!arenv[i])
		{
			free_dtab(arenv);
			return (print_error(errno, NULL));
		}
		i++;
		tmp = tmp->next;
	}
	return (arenv);
}


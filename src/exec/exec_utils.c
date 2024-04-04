/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:27:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/04 17:33:40 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_fds(t_fd *fd)
{
	fd->pfd[R] = 0;
	fd->pfd[W] = 0;
	fd->ffd = 0;
	fd->pid = -1;
	fd ->tmpin = 0;
}

void	close_fds(t_fd *fd, int code)
{
	if (fd->pfd[R] != 0)
		close (fd->pfd[R]);
	if (fd->pfd[W] != 0)
		close (fd->pfd[W]);
	if (code == EXE_ERR)
	{
		if (fd->tmpin != 0)
			close(fd->tmpin);
	}
	init_fds(fd);
}

static size_t	env_len(t_env *env)
{
	t_env	*tmp;
	size_t	n_nodes;

	tmp = env;
	n_nodes = 0;
	while (tmp)
	{
		n_nodes++;
		tmp = tmp->next;
	}
	return (n_nodes);
}

char	**arenvlst(t_env	*env)
{
	char	**arenv;
	size_t	i;
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (NULL);
	arenv = NULL;
	i = 0;
	arenv = malloc(sizeof(char *) * (env_len(env) + 1));
	if (!arenv)
		return (print_error(errno, NULL));
	arenv[env_len(env)] = 0;
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

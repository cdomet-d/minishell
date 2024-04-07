/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:27:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/07 19:39:56 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_fds(t_fd *fd)
{
	fd->pfd[R] = 0;
	fd->pfd[W] = 0;
	fd->ffd = 0;
	fd->pid = -1;
	fd ->tmpin = 1000;
}

void	close_fds(t_fd *fd, int code)
{
	(void)code;
	fprintf(stderr, "closing... %d\n", fd->pfd[R]);
	if (fd->pfd[R] != 0)
		if (close(fd->pfd[R]) == -1)
			print_error(0, "failed to close fd->pfd[R]");
	fprintf(stderr, "closing... %d\n", fd->pfd[W]);
	if (fd->pfd[W] != 0)
		if (close(fd->pfd[W]) == -1)
			print_error(0, "failed to close fd->pfd[W]");
	init_fds(fd);
}

void exe_failure(t_fd *fd, t_input *in, char **arenv)
{
	close(fd->tmpin);
	free_dtab(arenv);
	env_freelst(in->env);
	input_freelst(&in);
	print_error(errno, NULL);
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

bool	is_first_cmd(t_input *in)
{
	t_input *tmp;
	bool	first;

	tmp = in;
	first = true;
	if (tmp->prev == NULL)
		return (first);
	while (tmp)
	{
		tmp = tmp->prev;
		if (tmp && tmp->tok == command)
			first = false;
	}
	return (first);
}

bool	is_last_cmd(t_input *in)
{
	t_input *tmp;
	bool	last;

	tmp = in;
	last = true;
	if (tmp->next == NULL)
		return (last);
	while (tmp)
	{
		tmp = tmp->next;
		if (tmp && tmp->tok == command)
			last = false;
	}
	return (last);
}



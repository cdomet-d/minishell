/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 23:32:19 by jauseff           #+#    #+#             */
/*   Updated: 2024/05/16 20:41:01 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	path(t_input *in)
{
	t_env	*tmpenv;
	if (!in || !in->env)
		return (false);
	tmpenv = in->env;
	while (tmpenv)
	{
		if (ft_strncmp(tmpenv->env, "PATH=", 5) == 0)
			return (true);
		tmpenv = tmpenv->next;
	}
	return (false);
}

void	*killchild(t_fd *fd, t_input *in)
{
	int		e_stat;
	t_input	*last;

	last = get_last_node(in);
	if (builtin_true(last))
		e_stat = in->status;
	else
		e_stat = 1;
	close_pfd(fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (in && in->env)
		env_freelst(&in->env);
	input_freelst(&in);
	exit(e_stat);
}

void	display_exec_error(t_input	*in, int err)
{
	struct stat	infos;

	if (in->data[0] && stat(in->data[0], &infos) != -1)
		if (S_ISDIR(infos.st_mode))
			printf("%s: %s: %s\n", "minishell", in->data[0], "is a directory");
	if (path(in))
	{
		if (in->data && in->data[0] && access(in->data[0], X_OK) == -1)
			printf("%s: %s: %s\n", "minishell", in->data[0], "command not found");
	}
	else
	{
		if (in->data && in->data[0] && access(in->data[0], X_OK) == -1)
			printf("%s: %s: %s\n", "minishell", in->data[0], strerror(err));
	}
}

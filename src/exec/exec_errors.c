/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 23:32:19 by jauseff           #+#    #+#             */
/*   Updated: 2024/05/23 13:29:01 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_input	*get_last_executable(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->prev)
	{
		if (op_true(tmp, command) || builtin_true(tmp))
			return (tmp);
		tmp = tmp->prev;
	}
	return (tmp);
}

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

	last = get_last_executable(in);
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

void	display_exec_error(t_input	*in)
{
	struct stat	infos;

	if (!in->data || !in->data[0])
		return ;
	if (!path_slash(in->data[0]) && path(in))
		verror("minishell: ", in->data[0], ": command not found");
	else if (in->data[0] && stat(in->data[0], &infos) == -1)
	{
		if (errno == ENOENT)
			verror("minishell: ", in->data[0], ": no such file or directory");
		else
			print_error(errno, "minishell");
	}
	else if (S_ISDIR(infos.st_mode))
		verror("minishell: ", in->data[0], ": Is a directory");
	else if (access(in->data[0], X_OK))
		print_error(errno, "minishell");
}

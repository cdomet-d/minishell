/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:05:08 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/21 19:35:50 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	init_rv(t_input *in)
{
	t_input	*head;

	if (!in)
		return ;
	head = in;
	while (in)
	{
		if (in->next)
			in->next->status = in->status;
		in->head = head;
		in = in->next;
	}
	in = head;
}

void	init_exec(t_input *in, t_input **tmp, t_fd *fd)
{
	init_rv(in);
	init_fds(fd, in);
	*tmp = in;
}

void	close_and_wait(t_input *in, t_fd *fd)
{
	int			e_stat;

	e_stat = 0;
	if (count_pipes(in))
		close_pipe_read(fd);
	waitpid(fd->pid, &e_stat, 0);
	while (wait(0) != -1 && errno != ECHILD)
		;
	set_status(in, e_stat);
}

void	*create_child(t_fd *fd)
{
	if (fd->pnb != 0)
		if (pipe(fd->pfd) == -1)
			return (print_error(errno, "minishell: exec"));
	fd->pid = fork();
	if (fd->pid == -1)
		return (print_error(errno, "minishell: exec"));
	if (fd->pid == 0)
		signal(SIGQUIT, SIG_DFL);
	return ((int *)true);
}

void	*save_pipin(t_fd *fd)
{
	fd->pnb--;
	if (fd->tmpin != -1)
		if (close(fd->tmpin) == -1)
			print_error(errno, "minishell: exec");
	fd->tmpin = fd->pfd[R];
	close_pipe_write(fd);
	return ((int *)true);
}

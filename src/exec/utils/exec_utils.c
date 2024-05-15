/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:05:08 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/15 14:32:59 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_input	*get_last_node(t_input *in)
{
	t_input	*tmp;

	tmp = in;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
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

void	*create_child(t_input *in, t_fd *fd)
{
	printf("pipe : %ld\n", fd->pnb);
	(void)in;
	if (fd->pnb != 0)
	{
		// fprintf(stderr, "%.20s\n", "-- pipe ------------------");
		if (pipe(fd->pfd) == -1)
			return (print_error(errno, "create_child (piping)"));
	}
	fprintf(stderr, "%.20s\n", "-- fork ------------------");
	fd->pid = fork();
	if (fd->pid == -1)
		return (print_error(errno, "create_child (forking)"));
	if (fd->pid == 0)
		signal(SIGQUIT, SIG_DFL);
	return ((int *)true);
}

void	*save_pipin(t_fd *fd)
{
	// fprintf(stderr, "%.20s\n", "-- save pipin ------------------");
	fd->pnb--;
	if (fd->tmpin != -1)
		if (close(fd->tmpin) == -1)
			print_error(errno, "close_exec (tmpin)");
	fd->tmpin = fd->pfd[R];
	close_pipe_write(fd);
	return ((int *)true);
}

void	init_rv(t_input *in)
{
	t_input	*head;
	int		status;

	head = in;
 	status = in->status;
	while (in)
	{
		in->status = status;
		in = in->next;
	}
	in = head;
}

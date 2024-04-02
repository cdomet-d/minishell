/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/02 18:30:04 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*exec_cmd(t_input *in)
{
	t_input	*tmp;
	t_fd	fd;

	init_fd(&fd);
	tmp = in;
	while (tmp)
	{
		if (fd.pid != 0)
		{
			if (pipe_true(in))
			{
				if (pipe(fd.pfd) == -1)
					return (print_error(errno, NULL));
			}
			fd.pid = fork();
			if (fd.pid == -1)
				return (print_error(errno, NULL));
		}
		if (fd.pid == 0)
		{
			print_in_node(tmp);
			if (pipe_true(in))
				pip_redir(&fd);
			else if (tmp->tok == inredir)
				in_redir(&fd, in);
			else if (tmp->tok == outredir)
				out_redir(&fd, in);
			else if (tmp->tok == command)
				execve(in->data[0], in->data, arenvlst(in->env));
			if (dup2(fd.tmpin, fd.pfd[R]) == -1)
				return (print_error(errno, NULL));
			// exit(1);
		}
		tmp = tmp->next;
		if (fd.pfd[R] != 0)
			close (fd.pfd[R]);
		if (fd.pfd[W] != 0)
			close (fd.pfd[W]);
		while (wait(0) != -1 && errno != ECHILD)
		;
	}
	if (fd.tmpin != 0)
		close(fd.tmpin);
	return ("fckdat");
}

void	*out_redir(t_fd *fd, t_input *in)
{
	fd->ffd = open(in->data[0], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd->ffd == -1)
		return (print_error(errno, NULL));
	if (dup2(fd->ffd, STDOUT_FILENO) == -1)
		return (print_error(errno, NULL));
	close(fd->ffd);
	return ("fdat");
}

void	*in_redir(t_fd *fd, t_input *in)
{
	if (access(in->data[0], R_OK) == -1)
	{
		print_error(errno, NULL);
		fd->ffd = open("/dev/null", O_RDONLY);
	}
	else
		fd->ffd = open(in->data[0], O_RDONLY);
	if (fd->ffd == -1)
		return (print_error(errno, NULL));
	if (dup2(fd->ffd, STDIN_FILENO) == -1)
		return (print_error(errno, NULL));
	close(fd->ffd);
	return ("fdat");
}

void	*pip_redir(t_fd *fd)
{
	if (dup2(fd->pfd[R], STDIN_FILENO))
		return (print_error(errno, NULL));
	if (dup2(fd->pfd[W], STDOUT_FILENO))
		return (print_error(errno, NULL));
	close (fd->pfd[R]);
	close (fd->pfd[W]);
	return ("hellya");
}

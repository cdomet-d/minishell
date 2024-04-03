/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/03 18:25:40 by cdomet-d         ###   ########lyon.fr   */
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
		if (fd.pid == -1)
		{
			if (pipe_true(in))
			{
				if (pipe(fd.pfd) == -1)
					return (print_error(errno, "opening pipe in exec_cmd"));
			}
			fd.pid = fork();
			if (fd.pid == -1)
				return (print_error(errno, "opening fork in exec_cmd"));
		}
		if (fd.pid == 0)
		{
			if (pipe_true(tmp))
			{
				pip_redir(&fd);
				if (dup2(fd.tmpin, fd.pfd[R]) == -1)
					return (print_error(errno, "duplicating pipe[R] in child"));
			}
			if (op_true(tmp, inredir))
				in_redir(&fd, tmp);
			else if (op_true(tmp, outredir))
				out_redir(&fd, tmp);
			if (tmp->tok == command)
				execve(in->data[0], in->data, arenvlst(in->env));
		}
		while (wait(0) != -1 && errno != ECHILD)
			;
		tmp = tmp->next;
		if (fd.pfd[R] != 0)
			close (fd.pfd[R]);
		if (fd.pfd[W] != 0)
			close (fd.pfd[W]);
	}
	if (fd.tmpin != 0)
		close(fd.tmpin);
	return ("fckdat");
}

void	*out_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	fprintf(stderr, "\033[0;35m\033[1m\n#==== OUTREDIR ====#\n\n\033[0m");
	tmp = find_redir(in, outredir);
	fd->ffd = open(tmp->data[0], O_CREAT | O_TRUNC | O_RDWR, 0777);
	print_fds(fd);
	if (fd->ffd == -1)
		return (print_error(errno, in->data[0]));
	if (dup2(fd->ffd, STDOUT_FILENO) == -1)
		return (print_error(errno, "duping out to file"));
	close(fd->ffd);
	fprintf(stderr, "\033[0;35m\033[1m\n#==================#\n\n\033[0m");
	return ("fdat");
}

void	*in_redir(t_fd *fd, t_input *in)
{
	t_input	*tmp;

	fprintf(stderr, "\033[0;35m\033[1m\n#==== INREDIR =====#\n\n\033[0m");
	tmp = find_redir(in, inredir);
	if (access(tmp->data[0], R_OK) == -1)
	{
		print_error(errno, NULL);
		fd->ffd = open("/dev/null", O_RDONLY);
		if (fd->ffd == -1)
			return (print_error(errno, "opening /dev/null"));
	}
	else
		fd->ffd = open(tmp->data[0], O_RDONLY);
	print_fds(fd);
	if (fd->ffd == -1)
		return (print_error(errno, "opening infile"));
	if (dup2(fd->ffd, STDIN_FILENO) == -1)
		return (print_error(errno, "duping in to file"));
	// close(fd->ffd);
	fprintf(stderr, "\033[0;35m\033[1m\n#==================#\n\n\033[0m");
	return ("fdat");
}

void	*pip_redir(t_fd *fd)
{
	fprintf(stderr, "\033[0;35m\033[1m\n#==== PIPREDIR =====#\n\n\033[0m");
	if (dup2(fd->tmpin, STDIN_FILENO))
		return (print_error(errno, "duping tempin to in"));
	if (dup2(fd->pfd[W], STDOUT_FILENO))
		return (print_error(errno, "duping pipe[out] to out"));
	close (fd->pfd[R]);
	close (fd->pfd[W]);
	fprintf(stderr, "\033[0;35m\033[1m\n#===================#\n\n\033[0m");
	return ("hellya");
}

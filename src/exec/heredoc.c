/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:51:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/26 16:27:28 by csweetin         ###   ########.fr       *//*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	in_line(t_input *in, char *line, int fd)
{
	if (in->data[0][0] < 0)
		if (search_dollar_hd(line))
			if (heredoc_expand(&line, in))
				return (1);
	if (write(fd, line, ft_strlen(line)) == -1)
		return (print_error(errno, "minishell: heredoc: "), 1);
	free(line);
	if (write(fd, "\n", 1) == -1)
		return (print_error(errno, "minishell: heredoc: "), 1);
	return (0);
}

static void	*h_gnl(int fd, t_input *in)
{
	char	*line;
	char	*tmpdel;

	rl_event_hook = get_nonull;
	line = NULL;
	tmpdel = get_delim(in);
	if (!tmpdel)
		return (NULL);
	while (1)
	{
		if (line)
			if (in_line(in, line, fd))
				return (free(line), free(tmpdel), NULL);
		sigend();
		line = readline(" > ");
		if (!line)
			return (free(tmpdel), free(line), print_error(0, "minishell: \
				warning: expected delimiter"));
		if (exit_loop(line, tmpdel, in))
			break ;
	}
	in->data[0][0] *= -1;
	return (free(tmpdel), free(line), (int *) true);
}

static char	*gen_filename(int fn)
{
	char	*strfn;
	char	*filename;

	strfn = ft_itoa(fn);
	if (!strfn)
		return (print_error(errno, "minishell: heredoc: "));
	filename = ft_strjoin("/tmp/tmp_", strfn);
	if (!filename)
		return (print_error(errno, "minishell: heredoc: )"));
	free(strfn);
	return (filename);
}

static void	*create_hfile(t_fd *fd, t_input *tmp, char *filename)
{
	fd->hfd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd->hfd == -1)
		return (print_error(errno, "minishell: heredoc: "));
	if (!h_gnl(fd->hfd, tmp))
		return (free (filename), close(fd->hfd), NULL);
	free(filename);
	if (close(fd->hfd) == -1)
		return (print_error(errno, "minishell: heredoc: "));
	return ((int *) true);
}

void	*create_hdocs(t_fd *fd, t_input *in)
{
	t_input	*tmp;
	int		fn;

	fn = 0;
	tmp = find_here(in, false);
	while (op_true(tmp, heredoc))
	{
		if (!create_hfile(fd, tmp, gen_filename(fn)))
			return (NULL);
		free(tmp->data[0]);
		in->status = tmp->status;
		tmp->data[0] = gen_filename(fn);
		tmp = find_here(tmp, true);
		fn++;
	}
	set_status(in, 0);
	return ((int *) true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:51:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/17 15:30:48 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	in_line(t_input *in, char *line, int fd)
{
	if (in->data[0][0] < 0)
		if (search_dollar_hd(line))
			if (heredoc_expand(&line, in))
				return (1);
	if (write(fd, line, ft_strlen(line)) == -1)
		return (print_error(errno, "minishell: heredoc"), 1);
	free(line);
	if (write(fd, "\n", 1) == -1)
		return (print_error(errno, "minishell: heredoc"), 1);
	return (0);
}

static void	*h_rl(int fd, t_input *in)
{
	char	*line;
	char	*tmpdel;

	line = NULL;
	tmpdel = get_delim(in);
	if (!tmpdel)
		return (NULL);
	while (1)
	{
		if (line)
			if (in_line(in, line, fd))
				return (heredoc_error(in, tmpdel, line, false));
		line = readline("\033[38;5;206m🌸 ↪️\033[0m ");
		if (!line)
			return (heredoc_error(in, tmpdel, line, true));
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
		return (print_error(errno, "minishell: heredoc"));
	filename = ft_strjoin("/tmp/tmp_", strfn);
	if (!filename)
		return (print_error(errno, "minishell: heredoc"));
	free(strfn);
	return (filename);
}

static void	*create_hfile(t_fd *fd, t_input *tmp, char *filename)
{
	fd->hfd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd->hfd == -1)
		return (print_error(errno, "minishell: heredoc"));
	if (!h_rl(fd->hfd, tmp))
		return (free (filename), close(fd->hfd), NULL);
	free(filename);
	if (close(fd->hfd) == -1)
		return (print_error(errno, "minishell: heredoc"));
	return ((int *) true);
}

void	*create_hdocs(t_fd *fd, t_input *in)
{
	t_input	*tmp;
	int		fn;

	fn = 0;
	tmp = find_here(in, false);
	if (!tmp)
		return (NULL);
	while (op_true(tmp, heredoc))
	{
		tmp->status = 0;
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

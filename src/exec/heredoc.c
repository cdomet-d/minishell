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
		return (print_error(errno, "heredoc (write))"), 1);
	free(line);
	if (write(fd, "\n", 1) == -1)
		return (print_error(errno, "heredoc (write))"), 1);
	return (0);
}

static void	*h_gnl(int fd, t_input *in, char *filename)
{
	char	*line;
	char	*tmpdel;

	(void)filename;
	rl_event_hook = get_nonull;
	fprintf(stderr, "%.20s\n", "-- h_gnl -----------------------------");
	line = NULL;
	tmpdel = ft_strdup(in->data[0]);
	if (!tmpdel)
		return (print_error(errno, NULL));
	if (in->data[0][0] < 0)
		tmpdel[0] *= -1;
	while (1)
	{
		if (line)
			if (in_line(in, line, fd))
				return (free(line), free(tmpdel), NULL);
		sigend();
		line = readline(" > ");
		if (!line)
			return (print_error(errno, "heredoc (GNL)"));
		if (ft_strncmp(line, tmpdel, (ft_strlen(in->data[0]))) == 0 || g_sig == SIGINT)
		{
			rl_event_hook = NULL;
			break ;
		}
	}
	free(tmpdel);
	in->data[0][0] *= -1;
	return ((int *) true);
}

static char	*gen_filename(int fn)
{
	char	*strfn;
	char	*filename;

	strfn = ft_itoa(fn);
	if (!strfn)
		return (print_error(errno, "gen_filename (itoa fn)"));
	filename = ft_strjoin("/tmp/tmp_", strfn);
	if (!filename)
		return (print_error(errno, "gen_filename (strjoin filename)"));
	free(strfn);
	return (filename);
}

static void	*create_hfile(t_fd *fd, t_input *tmp, char *filename)
{
	// fprintf(stderr, "%.20s\n", "-- create_hfile --------------------------");
	fd->hfd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd->hfd == -1)
		return (print_error(errno, "create_hfile (opening tmp)"));
	if (!h_gnl(fd->hfd, tmp, filename))
		return (print_error(errno, "create_hfile (h_gnl)"));
	if (close(fd->hfd) == -1)
		return (print_error(errno, "create_hfile (closing hfd)"));
	free(filename);
	return ((int *) true);
}

void	*create_hdocs(t_fd *fd, t_input *in)
{
	t_input	*tmp;
	int		fn;

	fprintf(stderr, "%.20s\n", "-- create_hdocs -----------------------------");
	fn = 0;
	tmp = find_here(in, false);
	while (op_true(tmp, heredoc))
	{
		fprintf(stderr, "%.20s\n", "-- in loop -----------------------------");
		print_fds(fd);
		if (!create_hfile(fd, tmp, gen_filename(fn)))
			return (print_error(errno, "prep h_file (creating a file)"));
		free(tmp->data[0]);
		tmp->data[0] = gen_filename(fn);
		tmp = find_here(tmp, true);
		fn++;
	}
	return ((int *) true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:51:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/25 18:34:02 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	*h_gnl(int fd, t_input *in)
{
	char	*line;
	char	*temp;
	char	*tempdata;
	int		letter;

	fprintf(stderr, "%.20s\n", "-- h_gnl -----------------------------");
	fprintf(stderr, "\033[2mdelim : [%s]\033[0m\n", in->data[0]);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (print_error(errno, "heredoc(GNL))"));
	tempdata = ft_strdup(in->data[0]);
	if (!tempdata)
		return (print_error(errno, NULL));
	if (in->data[0][0] < 0)
		tempdata[0] *= -1;
	while (ft_strncmp(line, tempdata, (ft_strlen(in->data[0]))) != 0)
	{
		if (line)
		{
			if (in->data[0][0] < 0)
			{
				if (search_dollar(&line))
				{
					letter = nb_letter(line, &(in)->env);
					temp = ft_calloc(sizeof(char), letter + 1);
					if (!temp)
						return (free(temp), print_error(errno, NULL));
					ft_copy(line, temp, &(in)->env, 0);
					line = temp;
					// revert(&line);
				}
			}
			if (write(fd, line, ft_strlen(line)) == -1)
				return (print_error(errno, "heredoc (write))"));
			free (line);
		}
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (print_error(errno, "heredoc (GNL))"));
	}
	free(tempdata);
	in->data[0][0] *= -1;
	if (line)
		free(line);
	return ((int *) true);
}

static char	*gen_filename(int fn)
{
	char	*strfn;
	char	*filename;

	// fprintf(stderr, "%.20s\n", "-- gen_filename --------------------------");
	strfn = ft_itoa(fn);
	if (!strfn)
		return (print_error(errno, "gen_filename (itoa fn)"));
	filename = ft_strjoin("tmp_", strfn);
	if (!filename)
		return (print_error(errno, "gen_filename (strjoin filename)"));
	// fprintf(stderr, "\033[2mfile [%.20s]\033[0m\n", filename);
	free(strfn);
	return (filename);
}

static void	*create_hfile(t_fd *fd, t_input *tmp, char *filename)
{
	// fprintf(stderr, "%.20s\n", "-- create_hfile --------------------------");
	fd->hfd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd->hfd == -1)
		return (print_error(errno, "create_hfile (opening tmp)"));
	if (!h_gnl(fd->hfd, tmp))
		return (print_error(errno, "create_hfile (h_gnl)"));
	if (close(fd->hfd) == -1)
		return (print_error(errno, "create_hfile (closing hfd)"));
	tmp->tok = inredir;
	free(filename);
	return ((int *) true);
}

void	*create_hdocs(t_fd *fd, t_input *in)
{
	t_input	*tmp;
	int		fn;

	fprintf(stderr, "%.20s\n", "-- create_hdocs -----------------------------");
	tmp = find_tok(in, heredoc, false);
	fn = 0;
	while (op_true(tmp, heredoc))
	{
		if (!create_hfile(fd, tmp, gen_filename(fn)))
			return (print_error(errno, "prep h_file (creating a file)"));
		free(tmp->data[0]);
		tmp->data[0] = gen_filename(fn);
		tmp->tok = inredir;
		tmp = find_tok(tmp, heredoc, true);
		fn++;
	}
	return ((int *) true);
}

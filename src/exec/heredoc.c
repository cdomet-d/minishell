/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:51:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/12 18:11:28 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*create_hfile(t_fd *fd, t_input *in)
{
	char	*line[2];
	t_input	*tmp;

	fprintf(stderr, "%.20s\n", "-- create_hfile -----------------------------");
	line[1] = NULL;
	tmp = in;
	tmp = find_tok(tmp, heredoc, 0);
	fd->hfd = open("tmp", O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd->hfd == -1)
		return (print_error(errno, "heredoc(opening tmp)"));
	line[0] = get_next_line(STDIN_FILENO);
	if (!line[0])
		return (print_error(errno, "heredoc(GNL))"));
	while (ft_strncmp(line[0], tmp->data[0], (ft_strlen(tmp->data[0]))) != 0)
	{
		if (line[0])
		{
			// check_for_dollar()
			// expand(line, &tmp->env, 0);
			if (write(fd->hfd, line[0], ft_strlen(line[0])) == -1)
				return (print_error(errno, "heredoc (write))"));
			free (line[0]);
		}
		line[0] = get_next_line(STDIN_FILENO);
		if (!line[0])
			return (print_error(errno, "heredoc(GNL))"));
	}
	if (line[0])
		free(line[0]);
	return ((int *) true);
}

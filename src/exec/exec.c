/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:26:17 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/29 15:19:36 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #include "exec.h"

// void	*exec_cmd(t_input *in)
// {
// 	t_input	*tmp;
// 	t_fd	fd;

// 	init_fd(&fd);
// 	tmp = in;
// 	print_fds(&fd);
// 	// while (tmp)
// 	// {
// 	// 	if (tmp->tok == inredir)
// 	// 		in_redir(in);
// 	// }
// 	return ("fckdat");
// }

// void	*in_redir(t_fd *fd, t_input *in)
// {
// 	if (access(in->data[0], R_OK) == -1)
// 	{
// 		print_error(errno, NULL);
// 		fd->ffd = open("/dev/null", O_RDONLY);
// 	}
// 	else
// 		fd->ffd = open(in->data[0], O_RDONLY);
// 	if (fd->ffd == -1)
// 		return (print_error(errno, NULL));
// 	return ("fdat");
// }

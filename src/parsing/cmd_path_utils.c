/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:40:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/13 16:30:24 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	path_len(char *env, size_t *i)
{
	int	len;

	len = 0;
	while (env[*i] && env[*i] != ':')
	{
		*i += 1;
		len++;
	}
	return (len);
}

int	check_path(char **path)
{
	struct stat	buf;

	if (access(*path, X_OK) == 0)
	{
		if (stat(*path, &buf) == -1)
		{
			free(*path);
			*path = NULL;
			return (print_error(errno, "minishell: parsing"), 1);
		}
		if (S_ISDIR(buf.st_mode))
			return (0);
		return (1);
	}
	return (0);
}

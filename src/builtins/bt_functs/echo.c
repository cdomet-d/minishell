/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:57:47 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/16 17:32:15 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	cmp_opt(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] != '-')
		return (1);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo(char **data)
{
	size_t	i;
	bool	opt;

	i = 0;
	opt = false;
	if (data && data[1])
	{
		while (data[++i] && !cmp_opt(data[i]))
			opt = true;
		while (data && data[i])
		{
			if (signal(SIGPIPE, sighandler) || ft_putstr_fd(data[i], STDOUT_FILENO) == -1)
				return (1);
			i++;
			if (data[i])
				if (signal(SIGPIPE, sighandler) || write(1, " ", 1) == -1)
					return (1);
		}
	}
	if (opt == false)
		if (signal(SIGPIPE, sighandler) || write(1, "\n", 1) == -1)
			return (1);
	return (0);
}

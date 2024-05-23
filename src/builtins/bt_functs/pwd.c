/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:57:23 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/23 14:50:28 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	pwd(t_env *env)
{
	char	*str;

	str = NULL;
	str = find_var_env(env, "PWD=");
	if (!str || !str[0])
	{
		str = NULL;
		str = getcwd(str, 0);
		if (!str)
			return (print_error(errno, "minishell: exec"), 1);
		if (g_sig == SIGPIPE || ft_putendl_fd(str, STDOUT_FILENO) == -1)
			return (free(str), 1);
		free(str);
	}
	else if (g_sig == SIGPIPE || ft_putendl_fd(str, STDOUT_FILENO) == -1)
		return (free(str), 1);
	return (0);
}

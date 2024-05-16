/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:57:23 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/08 14:43:55 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (1);
		if (ft_putendl_fd(str, STDOUT_FILENO) == -1)
			return (free(str), 1);
		free(str);
	}
	else if (ft_putendl_fd(str, STDOUT_FILENO) == -1)
		return (free(str), 1);
	return (0);
}

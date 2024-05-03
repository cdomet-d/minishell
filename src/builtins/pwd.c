/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:57:23 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/03 17:57:25 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	pwd(t_env *env, char **data)
{
	char	*str;

	str = NULL;
	if (data[1])
	{
		if (ft_putstr_fd("pwd : too many arguments\n", 2) == -1)
			return (1);
		return (0);
	}
	str = find_var_env(env, "PWD=");
	if (!str)
	{
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

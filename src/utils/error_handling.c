/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:27:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/18 14:15:47 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	fatal_exit(t_input **lst, int error_code, char *error_message)
{
	if (lst && (*lst) && (*lst)->env)
		env_freelst((*lst)->env);
	if (lst && (*lst))
		input_freelst(lst);
	if (error_code || error_message)
		print_error(error_code, error_message);
	if (error_code > 0)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	free_env(t_env *lst, int error_code, char *error_message)
{
	if (lst)
		env_freelst(lst);
	if (error_code || error_message)
		print_error(error_code, error_message);
	if (error_code > 0)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

static void	*errjoin(int error_code, char *error_message)
{
	char	*error;
	char	*tmp;
	
	tmp = ft_strjoin(error_message, ": ");
	if (!tmp)
		return (NULL);
	error = ft_strjoin(tmp, strerror(error_code));
	if (!error)
		return (NULL);
	free(tmp);
	return (error);
}

void	*print_error(int error_code, char *error_message)
{
	char	*err;
	
	if (error_code && !error_message)
	{
		ft_putstr_fd("\033[0;31m", 2);
		ft_putendl_fd(strerror(error_code), STDERR_FILENO);
		ft_putstr_fd("\033[0m", 2);
	}	
	else if (!error_code && error_message)
	{
		ft_putstr_fd("\033[0;31m", 2);
		ft_putendl_fd(error_message, STDERR_FILENO);
		ft_putstr_fd("\033[0m", 2);
	}
	else if (error_code && error_message)
	{
		err = errjoin(error_code, error_message);
		if (!err)
			return (print_error(0, "Congrats ! The error message crashed."));
		ft_putstr_fd("\033[1;31m", 2);
		ft_putendl_fd(err, 2);
		free(err);
		ft_putstr_fd("\033[0m", 2);
	}
	return (NULL);
}

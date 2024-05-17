/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:27:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/17 13:59:33 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	exit_no_input(t_env **env, char *line, int status)
{
	if (line)
		free (line);
	if (env && *env)
		env_freelst(env);
	exit(status);
}

void	fatal_exit(t_input **lst, int rv, char *error_message)
{
	rl_clear_history();
	if (lst && (*lst) && (*lst)->env)
		env_freelst(&(*lst)->env);
	if (lst && (*lst))
		input_freelst(lst);
	if (error_message)
		print_error(0, error_message);
	if (rv > 0)
		exit(rv);
	else
		exit(EXIT_SUCCESS);
}

static void	*errjoin(int error_code, char *error_message)
{
	char	*error;
	char	*tmp;

	tmp = ft_strjoin(error_message, ": ");
	if (!tmp)
		return (print_error(0, "Congrats ! The error message crashed."));
	error = ft_strjoin(tmp, strerror(error_code));
	if (!error)
		return (print_error(0, "Congrats ! The error message crashed."));
	free(tmp);
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	free(error);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	return ((int *)true);
}

int	verbose_error(char *s1, char *s2, char *s3)
{
	if (ft_putstr_fd("\033[1;31m", STDERR_FILENO) == -1)
		return (-1);
	if (ft_putstr_fd(s1, STDERR_FILENO) == -1)
		return (-1);
	if (ft_putstr_fd(s2, STDERR_FILENO) == -1)
		return (-1);
	if (ft_putstr_fd(s3, STDERR_FILENO) == -1)
		return (-1);
	if (ft_putendl_fd("\033[0m", STDERR_FILENO) == -1)
		return (-1);
	return (1);
}

void	*print_error(int error_code, char *error_message)
{
	if (error_code && !error_message)
	{
		ft_putstr_fd("\033[1;31m", STDERR_FILENO);
		ft_putendl_fd(strerror(error_code), STDERR_FILENO);
		ft_putstr_fd("\033[0m", STDERR_FILENO);
	}
	else if (!error_code && error_message)
	{
		ft_putstr_fd("\033[1;31m", STDERR_FILENO);
		ft_putendl_fd(error_message, STDERR_FILENO);
		ft_putstr_fd("\033[0m", STDERR_FILENO);
	}
	else if (error_code && error_message)
		errjoin(error_code, error_message);
	return (NULL);
}

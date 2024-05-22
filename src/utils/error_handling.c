/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:27:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/21 19:35:54 by cdomet-d         ###   ########lyon.fr   */
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
	*lst = (*lst)->head;
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

int	verror(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*error_message;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (print_error(0, "Congrat ! The error message crashed"), 1);
	error_message = ft_strjoin(tmp, s3);
	if (!error_message)
		return (free(tmp), print_error(0, "Congrat ! The error message crashed"), 1);
	free(tmp);
	if (ft_putstr_fd("\033[1;31m", STDERR_FILENO) == -1)
		return (-1);
	if (ft_putstr_fd(error_message, STDERR_FILENO) == -1)
		return (-1);
	free(error_message);
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

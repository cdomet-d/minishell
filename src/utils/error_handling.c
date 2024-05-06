/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:27:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/06 17:43:51 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

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
	ft_putstr_fd("\033[1;31m", 2);
	ft_putendl_fd(error, 2);
	free(error);
	ft_putstr_fd("\033[0m", 2);
	return ((int *)true);
}

void	*print_error(int error_code, char *error_message)
{
	// fprintf(stderr, "%.20s\n", "-- print_error ------------------------------");
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
		errjoin(error_code, error_message);
	return (NULL);
}

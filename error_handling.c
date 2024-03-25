/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:27:38 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/25 12:46:16 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_input **lst, int error_code, char *error_message)
{
	if (lst && (*lst))
		input_freelst(lst);
	if (error_code || error_message)
		print_error(error_code, error_message);
	else
		exit(EXIT_FAILURE);
}

void	free_env(t_env *lst, int error_code, char *error_message)
{
	if (lst)
		env_freelst(lst);
	if (error_code || error_message)
		print_error(error_code, error_message);
	else
		exit(EXIT_FAILURE);
}

void	print_error(int error_code, char *error_message)
{
	if (error_code)
		ft_putendl_fd(strerror(error_code), STDERR_FILENO);
	if (error_message)
		ft_putendl_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

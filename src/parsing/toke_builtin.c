/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:22:58 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/15 16:23:00 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	find_builtin(t_input *node)
{
	if (!ft_strncmp(node->data[0], "echo", 5))
		node->tok = ms_echo;
	if (!ft_strncmp(node->data[0], "cd", 3))
		node->tok = ms_cd;
	if (!ft_strncmp(node->data[0], "pwd", 4))
		node->tok = ms_pwd;
	if (!ft_strncmp(node->data[0], "export", 7))
		node->tok = ms_export;
	if (!ft_strncmp(node->data[0], "unset", 6))
		node->tok = ms_unset;
	if (!ft_strncmp(node->data[0], "env", 4))
		node->tok = ms_env;
	if (!ft_strncmp(node->data[0], "exit", 5))
		node->tok = ms_exit;
}

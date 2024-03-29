/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:28:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/29 18:53:59 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//si $arg=NULL ou n'existe pas replace par rien

void	command_expand()
{

}

// void	op_expand(char *data, t_env **env)
// {
// 	int	i;

// 	i = 0;
// 	if (data[i++] == '\'')
// 	{
// 		while (data[i] && data[i] != '\'')
// 			i++;
		
// 	}
// }

void	expand(t_input *node, t_env **env)
{
	(void)env;
	if (node->tok == command)
		command_expand();
	// else
	// 	op_expand(node->data[0], env);
}

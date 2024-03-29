/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:45:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/29 17:34:38 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	create_input(t_input **input, t_env **env, char **data, int tok)
{
	t_input	*new;

	new = NULL;
	new = input_newnode(data, tok, *env);
	if (!new)
	{
		print_error(EXIT_FAILURE, NULL);
		free_dtab(data);
		input_freelst(input);
		return (1);
	}
	input_addback(input, new);
	return (0);
}

void	create_env(t_input **input, char **envp, t_env **env)
{
	int		i;
	t_env	*new;

	i = 0;
	new = NULL;
	while (envp[i])
	{
		new = env_newnode(envp[i]);
		if (!new)
			fatal_exit(input, errno, NULL);
		env_addback(env, new);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:45:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/05 13:10:04 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* to be removed : for debug only */
	int node = 0;
/* ------------------------------ */

void	create_input(t_input **input, t_env **env, char **data, int tok)
{
	t_input	*new;

	node++;	
	new = NULL;
	new = input_newnode(data, tok, *env);
	if (!new)
	{
		input_freelst(input);
		print_error(EXIT_FAILURE, NULL);
	}
	new->no = node;
	input_addback(input, new);
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

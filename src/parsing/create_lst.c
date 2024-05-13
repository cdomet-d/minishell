/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:45:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/06 17:43:42 by cdomet-d         ###   ########lyon.fr   */
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
		print_error(errno, NULL);
		free_dtab(data);
		input_freelst(input);
		return (1);
	}
	input_addback(input, new);
	return (0);
}

void	create_env(t_input **input, char **envp, t_env **env)
{
	size_t		i;
	t_env		*new;

	i = 0;
	new = NULL;
	if (!envp || !*envp)
		return ;
	while (envp[i])
	{
		new = env_newnode(envp[i]);
		if (!new)
		{
			env_freelst(env);
			fatal_exit(input, errno, NULL);
		}
		env_addback(env, new);
		i++;
	}
}

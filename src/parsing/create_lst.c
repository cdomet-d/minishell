/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:45:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/31 14:19:59 by cdomet-d         ###   ########.fr       */
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
		print_error(errno, "minishell: parsing");
		free_darr(data);
		input_freelst(input);
		return (1);
	}
	input_addback(input, new);
	return (0);
}

void	create_env(char **envp, t_env **env)
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
			print_error(errno, "minishell: parsing");
			exit(EXIT_FAILURE);
		}
		env_addback(env, new);
		i++;
	}
}

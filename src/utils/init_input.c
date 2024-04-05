/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:52:51 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/05 12:41:19 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_env(char **envp, t_env **env)
{
	size_t	i;
	t_env	*envnew;

	i = 0;
	while (envp[i])
	{
		envnew = env_newnode(envp[i]);
		if (!envnew)
			free_env(*env, errno, "Failure while initializing environnement");
		env_addback(env, envnew);
		i++;
	}
}


static int	token(char *str)
{
	if (str[0] == '|')
		return (pip);
	else if (str[0] == '<')
		return (inredir);
	else if (str[0] == '>')
		return (outredir);
	else
		return (command);
}

void	init_input(char *argv[], t_input **input, t_env *env)
{
	size_t	i;
	t_input	*inew;

	i = 1;
	while (argv[i])
	{
		inew = input_newnode(ft_split(argv[i], ' '), token(argv[i]), env);
		if (!inew)
			fatal_exit(input, errno, "Failure while initializing input");
		input_addback(input, inew);
		i++;
	}
}
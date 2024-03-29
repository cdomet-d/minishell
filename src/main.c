/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/28 18:05:28 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_input	*input;
	char	*line;

	(void)argv;
	line = NULL;
	env = NULL;
	input = NULL;
	if (argc != 1)
	{
		print_error(0, "Error : too many arguments");
		return (1);
	}
	create_env(&input, envp, &env);
	while (1)
	{
		line = readline("Minishell > "); //besoin de proteger readline ???
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0 && line[0])
		{
			env_freelst(env);
			exit(EXIT_SUCCESS);
		}
		parsing(&input, &env, line);
		t_input	*temp;
		int i = 1;
		int	j = 0;
		temp = input;
		while (temp)
		{
			printf("\n- - - node %d - - -\n\n", i);
			printf("tok: %d\n", temp->tok);
			if (temp->data)
			{
				j = 0;
				while (temp->data[j])
				{
					printf("data[%d]: %s\n", j, temp->data[j]);
					j++;
				}
			}
			printf("\n- - - - - - - - - -\n\n");
			temp = temp->next;
			i++;
		}
		input_freelst(&input);
	}
	return (0);
}

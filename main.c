/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:56 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/26 16:52:37 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int main(int argc, char **argv, char **envp)
{
	t_env   *env;
	t_input *input;
	char    *line;

	(void)argc;
	(void)argv;
	line = NULL;
	env = NULL;
	input = NULL;
	while (1)
	{
		create_env(envp, &env);
		line = readline("Minishell > ");
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0) //si line == NULL ca s'arrete
		{
			env_freelst(env);
			exit(EXIT_SUCCESS);
		}
		tokenization(&input, &env, line);
		int i = 1;
		while (input)
		{
			printf("\n- - - node %d - - -\n\n", i);
			printf("tok: %d\n", input->tok);
			if (input->data)
				printf("data: %s\n", input->data[0]);
			printf("\n- - - - - - - - - -\n\n");
			input = input->next;
			i++;
		}
		input_freelst(&input);
	}
	return (0);
}

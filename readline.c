/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:21:48 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/18 18:24:45 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	int		i;

	t_list	lst;

	i = 0;
	input = NULL;
	while (i < 500)
	{
		input = readline("Minishell > ");
		add_history(input);
		printf("%s\n", input);
		printf("%d\n", i);
		i++;
	}
	clear_history();
	free(input);
}

// exemple de node pour un pipe
/* 
	lst.token = operator;
	lst.litteral = "|";
	path = NULL;
	arg = NULL;
	env = NULL;
*/

// exemple de node pour une commande
/* 
	lst.token = cmd;
	lst.litteral = NULL;
	path = /bin/cat;
	arg = cat -e;
	env = env;
*/

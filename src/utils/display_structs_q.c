/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_structs_q.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:49:56 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/21 12:17:56 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	qpenum(int token)
{
	if (token == 0)
		fprintf(stderr, "%s ", "pipe");
	else if (token == 1)
		fprintf(stderr, "%s ", "inredir");
	if (token == 2)
		fprintf(stderr, "%s ", "outredir");
	if (token == 3)
		fprintf(stderr, "%s ", "append");
	if (token == 4)
		fprintf(stderr, "%s ", "heredoc");
	if (token == 5)
		fprintf(stderr, "%s ", "command");
	else if (token == 6)
		fprintf(stderr, "%s ", "echo");
	else if (token == 7)
		fprintf(stderr, "%s ", "cd");
	else if (token == 8)
		fprintf(stderr, "%s ", "pwd");
	else if (token == 9)
		fprintf(stderr, "%s ", "export");
	else if (token == 10)
		fprintf(stderr, "%s ", "unset");
	else if (token == 11)
		fprintf(stderr, "%s ", "env");
	else if (token == 12)
		fprintf(stderr, "%s ", "exit");
}

void	pmin(t_input *input, char *str)
{
	t_input	*head;

	head = input;
	fprintf(stderr, "\033[2m%.20s\n", "-- pmin ------------------");
	if (str)
		fprintf(stderr, "\033[2m%.20s\n", str);
	while (input)
	{
		qpenum(input->tok);
		if (input->data)
			display_dtab(input->data);
		fprintf(stderr, "(%d) ", input->status);
		input = input->next;
	}
	fprintf(stderr, "%.21s\n\033[0m", "\n--------------------------------------------\n\033[0m");
	input = head;
}

void	display_dtab(char **dtab)
{
	size_t	i;

	i = 0;
	while (dtab && dtab[i])
	{
		fprintf(stderr, "[%s] ", dtab[i]);
		i++;
	}
}

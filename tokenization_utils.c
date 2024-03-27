/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:42:21 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/27 15:45:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quote(char *line)
{
	int		i;
	int		quote;
	char	quotetype;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quotetype = line[i++];
			quote++;
			while (line[i] && line[i] != quotetype)
				i++;
			if (line[i] == quotetype)
				quote++;
		}
		i++;
	}
	if ((quote % 2) != 0)
		return (1);
	return (0);
}

char	**get_data(t_input **input, char *line, int *i)
{
	char	**data;

	data = NULL;
	while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
			|| line[*i] == ' '))
		*i += 1;
	if (line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
	{
		data = build_tab(line, i, 1);
		if (!data)
			input_freelst(input);
	}
	else
		print_error(0, "syntax error");
	return (data);
}

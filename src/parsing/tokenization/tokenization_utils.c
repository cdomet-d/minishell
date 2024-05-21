/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:42:21 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/17 14:55:53 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quote(char *line)
{
	size_t	i;
	size_t	quote;
	char	quotetype;

	i = 0;
	quote = 0;
	quotetype = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quotetype = line[i++];
			quote++;
			while (line[i] && line[i] != quotetype)
				i++;
			if (line[i] && line[i] == quotetype)
				quote++;
		}
		if (line[i])
			i++;
	}
	if ((quote % 2) != 0)
		return (1);
	return (0);
}

static int	syntax_error(char *line, size_t *i)
{
	if (line[*i] == '\0')
		print_error(0, "syntax error near unexpected token 'newline'");
	else if (line[*i] == '>' || line[*i] == '<' || line[*i] == '|')
	{
		if (ft_putstr_fd("\033[1;31m", STDERR_FILENO) == -1)
			return (1);
		if (ft_putstr_fd("minishell : syntax error near unexpected token ", 2) \
			== -1)
			return (1);
		if (ft_putchar_fd(line[*i], STDERR_FILENO) == -1)
			return (1);
		if (ft_putendl_fd("\033[0m", STDERR_FILENO) == -1)
			return (1);
	}
	return (2);
}

char	**get_data(t_input **input, char *line, size_t *i, int *rv)
{
	char	**data;

	data = NULL;
	while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
			|| line[*i] == ' '))
		*i += 1;
	if (line[*i] && line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
	{
		data = build_tab(line, i, 1);
		if (!data)
			input_freelst(input);
	}
	else
	{
		input_freelst(input);
		*rv = syntax_error(line, i);
	}
	return (data);
}

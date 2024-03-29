/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:19:47 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/29 17:26:34 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	loop_content(t_input **input, t_env **env, char *line, int *i)
{
	while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
			|| line[*i] == ' '))
		*i += 1;
	if (line[*i] && line[*i] == '<')
	{
		if (tok_inredir(input, env, line, i))
			return (1);
	}
	else if (line[*i] && line[*i] == '>')
	{
		if (tok_outredir(input, env, line, i))
			return (1);
	}
	else if (line[*i] && line[*i] == '|')
	{
		if (tok_pipe(input, env, line, i))
			return (1);
	}
	else if (line[*i])
	{
		if (tok_command(input, env, line, i))
			return (1);
	}
	return (0);
}

int	tokenization(t_input **input, t_env **env, char *line)
{
	int	i;

	i = 0;
	if (check_quote(line))
	{
		print_error(0, "minishell : syntax error missing quote");
		return (1);
	}
	while (line[i])
	{
		if (loop_content(input, env, line, &i))
			return (1);
	}
	return (0);
}

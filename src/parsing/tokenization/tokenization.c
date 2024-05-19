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

static int	loop_content(t_input **input, t_env **env, char *line, size_t *i)
{
	while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
			|| line[*i] == ' '))
		*i += 1;
	if (line[*i] && line[*i] == '<')
		return (tok_inredir(input, env, line, i));
	else if (line[*i] && line[*i] == '>')
		return (tok_outredir(input, env, line, i));
	else if (line[*i] && line[*i] == '|')
		return (tok_pipe(input, env, line, i));
	else if (line[*i])
		return (tok_command(input, env, line, i));
	return (0);
}

int	tokenization(t_input **input, t_env **env, char *line, int *status)
{
	size_t	i;
	int		rv;

	i = 0;
	rv = 0;
	if (check_quote(line))
	{
		print_error(0, "minishell : syntax error missing quote");
		*status = 2;
		return (1);
	}
	while (line[i])
	{
		rv = loop_content(input, env, line, &i);
		if (rv != 0)
		{
			if (rv == 2)
				*status = 2;
			return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:07:33 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/03 18:23:04 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	tok_inredir(t_input **input, t_env **env, char *line, size_t *i)
{
	char	**data;
	int		tok;
	int		rv;

	rv = 1;
	data = NULL;
	if (line[*i + 1] == '<')
	{
		tok = heredoc;
		*i += 1;
	}
	else
		tok = inredir;
	*i += 1;
	data = get_data(input, line, i, &rv);
	if (!data)
		return (rv);
	if (create_input(input, env, data, tok))
		return (1);
	if (check_opt(input, line, i))
		return (1);
	return (0);
}

int	tok_outredir(t_input **input, t_env **env, char *line, size_t *i)
{
	char	**data;
	int		tok;
	int		rv;

	rv = 1;
	data = NULL;
	if (line[*i + 1] == '>')
	{
		tok = append;
		*i += 1;
	}
	else
		tok = outredir;
	*i += 1;
	data = get_data(input, line, i, &rv);
	if (!data)
		return (rv);
	if (create_input(input, env, data, tok))
		return (1);
	if (check_opt(input, line, i))
		return (1);
	return (0);
}

int	tok_command(t_input **input, t_env **env, char *line, size_t *i)
{
	char	**data;
	size_t	word;

	word = 0;
	count_word(line, *i, &word);
	data = NULL;
	data = build_tab(line, i, word);
	if (!data)
	{
		input_freelst(input);
		return (1);
	}
	if (create_input(input, env, data, command))
		return (1);
	return (0);
}

int	tok_pipe(t_input **input, t_env **env, char *line, size_t *i)
{
	*i += 1;
	while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
			|| line[*i] == ' '))
		*i += 1;
	if (!*input || line[*i] == '\0' || line[*i] == '|')
	{
		input_freelst(input);
		print_error(0, "minishell : syntax error near unexpected token '|'");
		return (2);
	}
	if (create_input(input, env, NULL, pip))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:19:47 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/27 18:50:04 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tok_inredir(t_input **input, t_env **env, char *line, int *i)
{
	char	**data;
	int		tok;

	data = NULL;
	if (line[*i + 1] == '<')
	{
		tok = heredoc;
		*i += 1;
	}
	else
		tok = inredir;
	*i += 1;
	data = get_data(input, line, i);
	if (!data)
		input_freelst(input);
	else
		create_input(input, env, data, tok);
}

void	tok_outredir(t_input **input, t_env **env, char *line, int *i)
{
	char	**data;
	int		tok;

	data = NULL;
	if (line[*i + 1] == '>')
	{
		tok = append;
		*i += 1;
	}
	else
		tok = outredir;
	*i += 1;
	data = get_data(input, line, i);
	if (!data)
		input_freelst(input);
	else
		create_input(input, env, data, tok);
}

void	tok_command(t_input **input, t_env **env, char *line, int *i)
{
	char	**data;
	int		word;

	word = 0;
	count_word(line, *i, &word);
	data = NULL;
	data = build_tab(line, i, word);
	if (!data)
		input_freelst(input);
	else
		create_input(input, env, data, command);
}

int	tok_pipe(t_input **input, t_env **env, char *line, int *i)
{
	*i += 1;
	while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
			|| line[*i] == ' '))
		*i += 1;
	if (!*input || line[*i] == '|')
	{
		print_error(0, "minishell : syntax error near unexpected token '|'");
		return (1);
	}
	create_input(input, env, NULL, pip);
	return (0);
}

void	tokenization(t_input **input, t_env **env, char *line)
{
	int	i;

	i = 0;
	if (check_quote(line))
		return (print_error(0, "minishell : syntax error missing quote"));
	while (line[i])
	{
		while (line[i] && ((line[i] >= '\t' && line[i] <= '\r')
				|| line[i] == ' '))
			i++;
		if (line[i] == '<')
			tok_inredir(input, env, line, &i);
		else if (line[i] == '>')
			tok_outredir(input, env, line, &i);
		else if (line[i] == '|')
		{
			if (tok_pipe(input, env, line, &i))
				return ;
		}
		else
			tok_command(input, env, line, &i);
	}
}

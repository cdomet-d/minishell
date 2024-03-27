/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:19:47 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/27 15:56:49 by csweetin         ###   ########.fr       */
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

	data = NULL;
	data = build_tab(line, i, 0);
	if (!data)
		input_freelst(input);
	else
		create_input(input, env, data, command);
}

void	tok_pipe(t_input **input, t_env **env)
{
	if (!*input)
	{
		print_error(0, "minishell : syntax error near unexpected token '|'");
		return ;
	}
	create_input(input, env, NULL, pip);
}

void	tokenization(t_input **input, t_env **env, char *line)
{
	int	i;

	i = 0;
	if (check_quote(line))
	{
		print_error(0, "minishell : syntax error missing a quote");
		return ;
	}
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
			tok_pipe(input, env);
		else
			tok_command(input, env, line, &i);
		if (line[i])
			i++;
	}
}

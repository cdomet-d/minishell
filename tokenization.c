/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:19:47 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/26 19:51:26 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tok_inredir(t_input **input, t_env **env, char *line, int *i)
{
	char	**data;

	data = NULL;
	if (line[*i + 1] == '<')
	{
		create_input(input, env, NULL, heredoc);
		*i += 1;
	}
	else
	{
		*i += 1;
		while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r') || line[*i] == ' '))
			*i += 1;
		if (line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
		{
			data = build_tab(line, i, 1);
			if (!data)
				input_freelst(input);
			else
				create_input(input, env, data, inredir);
		}
		else
			print_error(0, "syntax error");
	}
}

void	tok_outredir(t_input **input, t_env **env, char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		create_input(input, env, NULL, append);
		*i += 1;
	}
	else
		create_input(input, env, NULL, outredir);
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

void	tokenization(t_input **input, t_env **env, char *line)
{
	int	i;

	i = 0;
	if (check_quote(line))
	{
		print_error(0, "syntax error : missing a quote");
		return ;
	}
	while (line[i])
	{
		while (line[i] && ((line[i] >= '\t' && line[i] <= '\r') || line[i] == ' '))
			i++;
		if (line[i] == '<')
			tok_inredir(input, env, line, &i);
		else if (line[i] == '>')
			tok_outredir(input, env, line, &i);
		else if (line[i] == '|')
			create_input(input, env, NULL, pip);
		else
			tok_command(input, env, line, &i);
		if (line[i])
			i++;
	}
}

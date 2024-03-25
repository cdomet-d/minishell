/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:19:47 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/25 18:00:29 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	create_input(t_input **input, t_env **env, char *str, int tok)
{
    t_input	*new;
	char	**data;
	// int		size;

	(void)str;
    new = NULL;
	data = NULL;
	// size = 0;
	// if (tok == command || tok == file || tok == delimiter)
	// {
		
	// }
    new = input_newnode(data, tok, *env);
	if (!new)
		free_all(input, errno, NULL);
	input_addback(input, new);
}

void	tok_inredir(t_input **input, t_env **env, char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		create_input(input, env, NULL, heredoc);
		*i += 1;
	}
	else
	{
		create_input(input, env, NULL, inredir);
		if (line[*i + 1] == '"')
			build_tab();
		while (line[*i + 1] != '<' || line[*i + 1] != '<' || line[*i + 1] != '<')
			;
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

void	tokenization(t_input **input, t_env **env, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] >= '\t' && line[i] <= '\r')
			i++;
		if (line[i] == '<')
			tok_inredir(input, env, line, &i);
		if (line[i] == '>')
			tok_outredir(input, env, line, &i);
		if (line[i] == '|')
			create_input(input, env, NULL, pip);
		i++;
	}
}

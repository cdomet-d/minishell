/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:19:47 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/26 15:50:40 by csweetin         ###   ########.fr       */
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
		while ((line[*i] >= '\t' && line[*i] <= '\r') || line[*i] == ' ')
			*i += 1;
		if (line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
		{
			data = build_tab(line, i, 1);
			if (!data)
				free_all(input, errno, NULL);
			if (data)
				create_input(input, env, data, inredir);
		}
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

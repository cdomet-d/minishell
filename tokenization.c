/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:19:47 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/25 19:27:58 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	create_input(t_input **input, t_env **env, char **data, int tok)
{
	t_input	*new;

	new = NULL;
	new = input_newnode(data, tok, *env);
	if (!new)
		free_all(input, errno, NULL);
	input_addback(input, new);
}

char	**build_tab(char *line, int *i, int word)
{
	char	**tab;
	int		letter;
	int		temp;
	int		quote;

	tab = NULL;
	quote = 0;
	// word = 0;
	letter = 0;
	tab = malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	temp = *i;
	while (line[temp] != ' ' && line[temp] != '>' && line[temp] != '<' && line[temp] != '|')
	{
		letter++;
		temp++;
	}
	word = 0;
	tab[word] = malloc(sizeof(char) * (letter + 1));
	if (!tab[word])
	{
		free_dtab(tab);
		return (NULL);
	}
	letter = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '>' && line[*i] != '<' && line[*i] != '|')
	{
		if (line[*i] == '"')
		{
			quote++;
			tab[word][letter++] = line[*i];
			*i += 1;
			while (line[*i] && line[*i] != '"')
			{
				tab[word][letter++] = line[*i];
				*i += 1;
			}
			if (line[*i] == '"')
				quote++;
		}
		if (line[*i])
		{
			tab[word][letter++] = line[*i];
			*i += 1;
		}
	}
	tab[word][letter] = '\0';
	tab[word + 1] = NULL;
	if ((quote % 2) != 0)
	{
		write(2, "syntax error\n", 13);
		free_dtab(tab);
		tab = NULL;
	}
	return (tab);
}

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
		create_input(input, env, NULL, inredir);
		*i += 1;
		while ((line[*i] >= '\t' && line[*i] <= '\r') || line[*i] == ' ')
			*i += 1;
		if (line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
		{
			data = build_tab(line, i, 1);
			if (!data)
				free_all(input, errno, NULL);
			if (data)
				create_input(input, env, data, file);
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

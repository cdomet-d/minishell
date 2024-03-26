/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:40:32 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/26 19:52:32 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	count_letter(char *line, int count)
{
	int		temp;
	int		quote;
	char	quotetype;

	quote = 0;
	temp = count;
	while (line[count] && line[count] != ' ' && line[count] != '>'
		&& line[count] != '<' && line[count] != '|')
	{
		if (line[count] == '"' || line[count] == '\'')
		{
			quotetype = line[count];
			quote++;
			while (line[count] && line[count] != '"')
				count++;
			if (line[count] == quotetype)
				quote++;
		}
		if (line[count])
			count++;
	}
	if ((quote % 2) != 0)
		return (-1);
	count -= temp;
	return (count);
}

void	fill_tab(char *line, int *i, char **tab, int letter)
{
	int	word;

	word = 0;
	tab[word] = NULL;
	tab[word] = malloc(sizeof(char) * (letter + 1));
	if (!tab[word])
		return ;//(free_dtab(tab), NULL);
	letter = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '>'
		&& line[*i] != '<' && line[*i] != '|')
	{
		if (line[*i] == '"')
		{
			tab[word][letter++] = line[*i];
			*i += 1;
			while (line[*i] && line[*i] != '"')
			{
				tab[word][letter++] = line[*i];
				*i += 1;
			}
		}
		if (line[*i])
		{
			tab[word][letter] = line[*i];
			letter++;
			*i += 1;
		}
	}
	tab[word][letter] = '\0';
	tab[word + 1] = NULL;
}

char	**build_tab(t_input **input, char *line, int *i, int word)
{
	char	**tab;
	int		letter;

	tab = NULL;
	letter = 0;
	// if (word != 1)
	// 	word = count_word();
	tab = malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	letter = count_letter(line, *i);
	if (letter == -1)
	{
		print_error(0, "syntax error\n");
		input_freelst(input);
	}
	fill_tab(line, i, tab, letter);
	return (tab);
}

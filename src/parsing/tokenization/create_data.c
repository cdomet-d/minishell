/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:40:32 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/27 18:49:31 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	count_word(char *line, int i, int *word)
{
	char	quotetype;

	while (line[i] && line[i] != '>' && line[i] != '<' && line[i] != '|')
	{
		if (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		{
			*word += 1;
			while (line[i] && (line[i] == ' '
					|| (line[i] >= '\t' && line[i] <= '\r')))
				i++;
		}
		if (line[i] == '"' || line[i] == '\'')
		{
			quotetype = line[i++];
			while (line[i] && line[i] != quotetype)
				i++;
		}
		if (line[i] && line[i] != '>' && line[i] != '<' && line[i] != '|')
			i++;
	}
	if ((line[i] == '\0' || line[i] == '>' || line[i] == '<' || line[i] == '|')
		&& line[i - 1] != ' ')
		*word += 1;
}

int	count_letter(char *line, int letter)
{
	int		temp;
	char	quotetype;

	temp = letter;
	while (line[letter] && line[letter] != ' ' && line[letter] != '>'
		&& line[letter] != '<' && line[letter] != '|')
	{
		if (line[letter] == '"' || line[letter] == '\'')
		{
			quotetype = line[letter++];
			while (line[letter] && line[letter] != quotetype)
				letter++;
		}
		if (line[letter])
			letter++;
	}
	letter -= temp;
	return (letter);
}

void	fill_tab(char *line, int *i, char **tab, int *word)
{
	int		letter;
	char	quotetype;

	letter = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '>'
		&& line[*i] != '<' && line[*i] != '|')
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			quotetype = line[*i];
			tab[*word][letter++] = line[*i];
			*i += 1;
			while (line[*i] && line[*i] != quotetype)
			{
				tab[*word][letter++] = line[*i];
				*i += 1;
			}
		}
		if (line[*i])
		{
			tab[*word][letter++] = line[*i];
			*i += 1;
		}
	}
	tab[*word][letter] = '\0';
}

char	**build_tab(char *line, int *i, int word)
{
	char	**tab;
	int		letter;
	int		j;

	tab = NULL;
	letter = 0;
	tab = ft_calloc(sizeof(char *), word + 1);
	if (!tab)
		return (print_error(errno, NULL));
	j = word;
	word = 0;
	while (j-- > 0)
	{
		while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
				|| line[*i] == ' '))
			*i += 1;
		letter = count_letter(line, *i);
		tab[word] = ft_calloc(sizeof(char), letter + 1);
		if (!tab[word])
			return (free_dtab(tab), print_error(errno, NULL));
		fill_tab(line, i, tab, &word);
		word++;
	}
	tab[word] = NULL;
	return (tab);
}

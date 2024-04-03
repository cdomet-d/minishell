/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:42:21 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/03 18:22:55 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			if (line[i] && line[i] == quotetype)
				quote++;
		}
		if (line[i])
			i++;
	}
	if ((quote % 2) != 0)
		return (1);
	return (0);
}

void	syntax_error(char *line, int *i)
{
	if (line[*i] == '\0')
		print_error(0, "syntax error near unexpected token 'newline'");
	else if (line[*i] == '>' || line[*i] == '<')
	{
		ft_putstr_fd("minishell : syntax error near unexpected token ", 2);
		ft_putchar_fd(line[*i], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

char	**get_data(t_input **input, char *line, int *i)
{
	char	**data;

	data = NULL;
	while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
			|| line[*i] == ' '))
		*i += 1;
	if (line[*i] && line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
	{
		data = build_tab(line, i, 1);
		if (!data)
			input_freelst(input);
	}
	else
	{
		input_freelst(input);
		syntax_error(line, i);
	}
	return (data);
}

int	tab_len(char **tab)
{
	int	size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

int	fill_tab_join(char **tab, char **newtab, int *word)
{
	int	letter;
	int	i;

	i = 0;
	while (tab[i])
	{
		letter = ft_strlen(tab[i]);
		newtab[*word] = ft_calloc(sizeof(char), letter + 1);
		if (!newtab[*word])
			return (1);
		letter = 0;
		while (tab[i][letter])
		{
			newtab[*word][letter] = tab[i][letter];
			letter++;
		}
		newtab[*word][letter] = '\0';
		*word += 1;
		i++;
	}
	return (0);
}

char	**tab_join(char **s1, char **s2)
{
	char	**tab;
	int		word;

	tab = NULL;
	word = tab_len(s1) + tab_len(s2);
	tab = ft_calloc(sizeof(char *), (word + 1));
	if (!tab)
		return (NULL);
	word = 0;
	if (fill_tab_join(s1, tab, &word))
		return (free_dtab(tab), free_dtab(s2), NULL);
	if (fill_tab_join(s2, tab, &word))
		return (free_dtab(tab), free_dtab(s2), NULL);
	tab[word] = NULL;
	free_dtab(s2);
	return (tab);
}

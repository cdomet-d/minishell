/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:09:30 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/31 14:19:59 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	tab_len(char **tab)
{
	size_t	size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

static int	fill_tab_join(char **tab, char **newtab, size_t *word)
{
	size_t	letter;
	size_t	i;

	i = 0;
	while (tab[i])
	{
		letter = ft_strlen(tab[i]);
		newtab[*word] = ft_calloc(sizeof(char), letter + 1);
		if (!newtab[*word])
			return (print_error(errno, "minishell: parsing"), 1);
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

static char	**tab_join(char **s1, char **s2)
{
	char	**tab;
	size_t	word;

	tab = NULL;
	word = tab_len(s1) + tab_len(s2);
	tab = ft_calloc(sizeof(char *), (word + 1));
	if (!tab)
		return (free_darr(s2), print_error(errno, "minishell: parsing"));
	word = 0;
	if (fill_tab_join(s1, tab, &word))
		return (free_darr(tab), free_darr(s2), NULL);
	if (fill_tab_join(s2, tab, &word))
		return (free_darr(tab), free_darr(s2), NULL);
	tab[word] = NULL;
	free_darr(s2);
	return (tab);
}

static int	add_opt(t_input **input, t_input *ptr, char *line, size_t *i)
{
	char	**new;
	char	**data;
	size_t	word;

	word = 0;
	new = NULL;
	data = NULL;
	count_word(line, *i, &word);
	data = build_tab(line, i, word);
	if (!data)
		return (input_freelst(input), 1);
	new = tab_join(ptr->data, data);
	if (!new)
		return (input_freelst(input), 1);
	free_darr(ptr->data);
	ptr->data = new;
	return (0);
}

int	check_opt(t_input **input, char *line, size_t *i)
{
	t_input	*ptr;

	ptr = *input;
	while (ptr->next)
		ptr = ptr->next;
	while (ptr && ptr->tok != pip)
	{
		if (ptr->tok == command)
		{
			while (line[*i] && ((line[*i] >= '\t' && line[*i] <= '\r')
					|| line[*i] == ' '))
				*i += 1;
			if (line[*i] && line[*i] != '<' && line[*i] != '>'
				&& line[*i] != '|')
				if (add_opt(input, ptr, line, i))
					return (1);
		}
		ptr = ptr->prev;
	}
	return (0);
}

//HEADER

#include "parsing.h"

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

int	add_opt(t_input **input, t_input *ptr, char *line, int *i)
{
	char	**new;
	char	**data;
	int		word;

	word = 0;
	new = NULL;
	data = NULL;
	count_word(line, *i, &word);
	data = build_tab(line, i, word);
	if (!data)
		return (input_freelst(input), 1);
	new = tab_join(ptr->data, data);
	if (!new)
		return (1);
	data = ptr->data;
	ptr->data = NULL;
	ptr->data = new;
	free_dtab(data);
    return (0);
}

int	check_opt(t_input **input, char *line, int *i)
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
			if (line[*i] && line[*i] != '<' && line[*i] != '>' && line[*i] != '|')
				if (add_opt(input, ptr, line, i))
					return (1);
		}
		ptr = ptr->prev;
	}
	return (0);
}

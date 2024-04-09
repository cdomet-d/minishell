//HEADER

#include "parsing.h"

void    fill_word(char *new, char *old, int i)
{
	int j;

	j = 0;
	while (old[j] && i > 0)
	{
		new[j] = old[j];
		j++;
		i--;
	}
}

int	nb_letter_str(char *data, int *j, int letter)
{
	char	quotetype;

	while (data[*j] && (data[*j] == ' ' || (data[*j] >= '\t' && data[*j] <= '\r')))
		*j += 1;
	while (data[*j] && data[*j] != ' ' && (data[*j] < '\t' || data[*j] > '\r'))
	{
		if (data[*j] && (data[*j] == '\'' || data[*j] == '"'))
		{
			quotetype = data[*j];
			*j += 1;
			letter += 1;
			while (data[*j] && data[*j] != quotetype)
			{
				letter += 1;
				*j += 1;
			}
		}
		if (data[*j])
		{
			letter += 1;
			*j += 1;
		}
	}
	return (letter);
}

char	**nb_letter(char **data, char **newtab)
{
	int i;
	int j;
	int	word;
	int	letter;

	i = 0;
	word = 0;
	while (data[i])
	{
		j = 0;
		while (data[i][j])
		{
			letter = nb_letter_str(data[i], &j, 0);
			newtab[word] = ft_calloc(sizeof(char), letter + 1);
			if (!newtab[word])
				return (free_dtab(newtab), NULL);
			fill_word(newtab[word], data[i] + (j - letter), letter);
			word += 1;
			if (data[i][j])
				j++;
		}
		i++;
	}
	return (newtab);
}


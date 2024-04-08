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

char	**nb_letter(char **data, t_env **env, char **newtab, int fd)
{
	int i;
	int j;
	int word;
	int letter;
	char    quotetype;

	(void)env;
	(void)fd;
	i = 0;
	word = 0;
	while (data[i])
	{
		letter = 0;
		j = 0;
		while (data[i][j])
		{
			while (data[i][j] && (data[i][j] == ' ' || (data[i][j] >= '\t' && data[i][j] <= '\r')))
				j++;
			while (data[i][j] && data[i][j] != ' ' && (data[i][j] < '\t' || data[i][j] > '\r'))
			{
				if (data[i][j] && (data[i][j] == '\'' || data[i][j] == '"'))
				{
					quotetype = data[i][j++];
					letter++;
					while (data[i][j] && data[i][j] != quotetype)
					{
						letter++;
						j++;
					}
				}
				if (data[i][j])
				{
					letter++;
					j++;
				}
			}
			newtab[word] = ft_calloc(sizeof(char), letter + 1);
			if (!newtab[word])
				return (free_dtab(newtab), NULL);
			fill_word(newtab[word], data[i] + (j - letter), letter);
			word += 1;
			letter = 0;
		}
		i++;
	}
	return (newtab);
}

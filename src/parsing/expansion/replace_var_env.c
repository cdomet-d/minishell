//HEADER

#include "parsing.h"

void	count_in_env(char *str, int *letter)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		*letter += 1;
		i++;
	}
}

void	ft_copy(char *data, char *newtab, t_env **env)
{
	int	i;
	int	j;
	int	n;
	char	*str;

	i = 0;
	j = 0;
	n = 0;
	str = NULL;
	while (data[i])
	{
		if (data[i] == '\'')
		{
			newtab[j++] = data[i++];
			while (data[i] && data[i] != '\'')
				newtab[j++] = data[i++];
		}
		if (data[i] == '$')
		{
			i++;
			n = 0;
			str = search_env(data + i, env);
			if (str)
			{
				while (str[n])
					newtab[j++] = str[n++];
			}
			while (data[i] && data[i] != '$' && data[i] != '\'' && data[i] != '"')
				i++;
		}
		else if (data[i])
			newtab[j++] = data[i++];
	}
}

char	**ft_replace(char **data, t_env **env)
{
	int word;
	int		letter;
	char    **newtab;
	int		j;

	word = 0;
	newtab = NULL;
	while (data[word])
		word++;
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (NULL);
	word = 0;
	while (data[word])
	{
		letter = 0;
		j = 0;
		while (data[word][j])
		{
			if (data[word][j] == '\'')
			{
				j++;
				letter++;
				while (data[word][j] && data[word][j] != '\'')
				{
					j++;
					letter++;
				}
			}
			if (data[word][j] == '$')
			{
				j++;
				count_in_env(search_env(data[word] + j, env), &letter);
				while (data[word][j] && data[word][j] != '$' && data[word][j] != '\'' && data[word][j] != '"')
					j++;
			}
			else if (data[word][j])
			{
				j++;
				letter++;
			}
		}
		newtab[word] = ft_calloc(sizeof(char), letter + 1);
		if (!newtab[word])
			return (free_dtab(newtab), NULL);
		ft_copy(data[word], newtab[word], env);
		word++;
	}
	return (newtab);
}

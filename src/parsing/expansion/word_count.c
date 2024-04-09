//HEADER

#include "parsing.h"


char	**nb_word(char **data, t_env **env, int *word)
{
	char	**newtab;
	int		i;
	int		j;
	char	quotetype;

	i = 0;
	quotetype = 0;
	newtab = ft_replace(data, env);
	if (!newtab)
		return (NULL);
	while (newtab[i])
	{
		j = 0;
		while (newtab[i][j])
		{
			if (newtab[i][j] == '\'' || newtab[i][j] == '"')
			{
				quotetype = newtab[i][j++];
				while (newtab[i][j] && newtab[i][j] != quotetype)
					j++;
			}
			if ((newtab[i][j] != ' ' && (newtab[i][j] < '\t' || newtab[i][j] > '\r')) && (newtab[i][j + 1] == ' '
				|| (newtab[i][j + 1] >= '\t' && newtab[i][j + 1] <= '\r') || newtab[i][j + 1] == '\0'))
				*word += 1;
			if (newtab[i][j])
				j++;
		}
		i++;
	}
	return (newtab);
}

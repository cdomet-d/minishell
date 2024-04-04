//HEADER

#include "parsing.h"

void	letter_env_quote(char *str, int *letter)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i += 1;
	i += 1;
	while (str[i])
	{
		*letter += 1;
		i++;
	}
}

void	nb_letter_env(char *str, int *letter, int *word)
{
    int i;
    
    i = 0;
	while (str[i] && str[i] != '=')
		i += 1;
	i += 1;
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;
	while (str[i])
	{
        if (str[i] != ' ' && (str[i] < '\t' || str[i] > '\r'))
		    *letter += 1;
        else
        {
            while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
                i++;
            // newtab[word] = ft_calloc(sizeof(char), letter + 1);
	        // if (!newtab)
	        // 	return (1);
	        // ft_fill();
            *letter = 0;
            *word += 1;
        }
		i++;
	}
}

void	nb_letter(char *str, t_env **env, int *letter, int *i)
{
	if (str[*i] == '\'')
	{
		*letter += 1;
		*i += 1;
		while (str[*i] && str[*i] != '\'')
		{
			*i += 1;
			*letter += 1;
		}
	}
	if (str[*i] == '"')
	{
		*i += 1;
		*letter += 1;
		while (str[*i] && str[*i] != '"')
		{
			if (str[*i] == '$')
				letter_env_quote(search_env(str + (*i + 1), env), letter);
			*i += 1;
			*letter += 1;
		}
	}
}

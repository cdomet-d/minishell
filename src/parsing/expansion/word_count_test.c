#include "parsing.h"

bool	nb_word_env(char *str, int *word, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && (str[i] < '\t' || str[i] > '\r'))
			&& (str[i + 1] == ' ' || (str[i + 1] >= '\t'
					&& str[i + 1] <= '\r')))
			*word += 1;
		i++;
	}
	if ((str[i - 1] == ' ' || (str[i - 1] >= '\t' && str[i - 1] <= '\r')) && (c == '\0'))// || c == '$'))
        return (true);
    return (false);
}

void	nb_word(char **data, t_env **env, int *word)
{
	int		i;
	int		j;
	char	quotetype;
	char	*str;
	char	*tmp;
	int		len;
	size_t	null;
	bool	dollar;

	i = 0;
	null = 0;
	len = 0;
	str = NULL;
	tmp = NULL;
	while (data[i])
	{
		dollar = false;
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] == '"' || data[i][j] == '\'')
			{
				quotetype = data[i][j++];
				while (data[i][j] && data[i][j] != quotetype)
					j++;
			}
			if (data[i][j] == '$')
			{
				null = 0;
				while (!str && data[i][j] && data[i][j] == '$')
				{
					str = search_env(data[i] + (j + 1), env);
					if (!str)
					{
						j++;
						null++;
						while (data[i][j] && data[i][j] != '$' && data[i][j] != '"'
							&& data[i][j] != '\'')
						{
							null++;
							j++;
						}
					}
				}
				len = ft_strlen(tmp) - 1;
				if (!str && data[i][j] == '\0' && tmp && (tmp[len] == ' ' || (tmp[len] >= '\t' && tmp[len] <= '\r')))
					dollar = true;
				if (null == ft_strlen(data[i]))
					dollar = true;
				if (str)
				{
					if (null == 0)
						null = 1;
					if (j != 0 && data[i][j - null] < 0)
					{
						len = ft_strlen(tmp) - 1;
						if (tmp && tmp[len] != ' ' && (tmp[len] < '\t' || tmp[len] > '\r')
							&& (str && (str[0] == ' ' || (str[0] >= '\t' && str[0] <= '\r'))))
							*word += 1;
					}
					if (j != 0 && (j - null) > 0 && data[i][j - null] > 0 && ((str && (str[0] == ' ' || (str[0] >= '\t' && str[0] <= '\r')))))
						*word += 1;
					tmp = str;
					j++;
					while (data[i][j] && data[i][j] != '$' && data[i][j] != '"'
						&& data[i][j] != '\'')
					{
						data[i][j] *= -1;
						j++;
					}
					dollar = nb_word_env(str, word, data[i][j]);
					str = NULL;
				}
			}
			else if (data[i][j])
				j++;
		}
		if (dollar == false)
            *word += 1;
		i++;
	}
}

#include "parsing.h"

void	ft_copy_env(char *data, char *newtab, t_env **env, int *j)
{
	int		i;
	char	*str;

	i = 0;
	str = search_env(data, env);
	if (str)
	{
		while (str[i])
		{
			newtab[*j] = str[i];
			*j += 1;
			i++;
		}
	}
}

void	ft_copy(char *data, char *newtab, t_env **env, int rv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] && data[i] == '$')
		{
			i++;
			if (data[i] == '?')
			{
				newtab[j++] = 48 + rv;
				i++;
			}
			else if (data[i])
			{
				ft_copy_env(data + i, newtab, env, &j);
				while (data[i] && data[i] != '$'  && data[i] > 0
					&& data[i] != '"' && data[i] != ' '
					&& (data[i] > '\t' || data[i] < '\r') && data[i] != '-')
					i++;
			}
		}
		else if (data[i] < 0)
		{
			while (data[i] && data[i] < 0)
				newtab[j++] = data[i++];
		}
		else if (data[i])
			newtab[j++] = data[i++];
	}
}

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

void    put_in_neg(char *data)
{
	int i;

	i = 0;
	while (data[i])
	{
		if (data[i] == ' ' || (data[i] >= '\t' && data[i] <= '\r'))
			data[i] *= -1;
		if (data[i] == '"')
		{
			i++;
			while (data[i] && data[i] != '"')
				i++;
		}
		if (data[i] == '\'')
		{
			data[i++] *= -1;
			while (data[i] && data[i] != '\'')
				data[i++] *= -1;
			data[i++] *= -1;
		}
		else if (data[i])
			i++;
	}
}

int	letters(char *data, t_env **env)
{
	int	letter;
	int	j;

	letter = 0;
	j = 0;
	put_in_neg(data);
	while (data[j])
	{
		if (data[j] == '$')
		{
			j++;
			if (data[j] && data[j] == '?')
			{
				j++;
				letter++;
			}
			else if (data[j])
			{
				count_in_env(search_env(data + j, env), &letter);
				while (data[j] && data[j] != '$' && data[j] > 0
					&& data[j] != '"' && data[j] != ' '
					&& (data[j] > '\t' || data[j] < '\r') && data[j] != '-')
					j++;
			}		
		}
		else if (data[j] && data[j] < 0)
		{
			while (data[j] && data[j] < 0)
			{
				j++;
				letter++;
			}
		}
		else if (data[j])
		{
			j++;
			letter++;
		}
	}
	return (letter);
}

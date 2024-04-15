/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:43:58 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/15 16:43:09 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_copy_env(char *data, char *newtab, t_env **env, int *j)
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
	i = 0;
	while (data[i] && (ft_isalnum(data[i]) || data[i] == '_'))
		i++;
	return (i);
}

void	ft_copy(char *data, char *newtab, t_env **env, int rv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '$' && data[i + 1] && (ft_isalnum(data[i + 1])
				|| data[i + 1] == '_' || data[i + 1] == '?'))
		{
			i++;
			if (data[i] && data[i] == '?')
			{
				newtab[j++] = 48 + rv;
				i++;
			}
			else if (data[i] && ft_isdigit(data[i]))
				i++;
			else if (data[i])
				i += ft_copy_env(data + i, newtab, env, &j);
		}
		else if (data[i])
			newtab[j++] = data[i++];
	}
}

void	nb_letter_env(char *data, t_env **env, int *letter, int *j)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	*j += 1;
	if (data[*j] && data[*j] == '?')
	{
		*j += 1;
		*letter += 1;
	}
	else if (data[*j] && ft_isdigit(data[*j]))
		*j += 1;
	else if (data[*j])
	{
		str = search_env(data + *j, env);
		if (str)
		{
			while (str[i++])
				*letter += 1;
		}
		while (data[*j] && (ft_isalnum(data[*j]) || data[*j] == '_'))
			*j += 1;
	}
}

int	nb_letter(char *data, t_env **env)
{
	int	letter;
	int	j;

	letter = 0;
	j = 0;
	while (data[j])
	{
		if (data[j] == '$' && data[j + 1] && (ft_isalnum(data[j + 1])
				|| data[j + 1] == '_' || data[j + 1] == '?'))
			nb_letter_env(data, env, &letter, &j);
		else if (data[j] < 0)
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

char	**expand(char **data, t_env **env, int rv)
{
	int		word;
	int		letter;
	char	**newtab;

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
		letter = nb_letter(data[word], env);
		newtab[word] = ft_calloc(sizeof(char), letter + 1);
		if (!newtab[word])
			return (free_dtab(newtab), NULL);
		ft_copy(data[word], newtab[word], env, rv);
		word++;
	}
	newtab[word] = NULL;
	return (newtab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:23:05 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/04 19:44:47 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	letter_env_quote(char *str, int *letter)
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

int	nb_letter_env(char *str, int *letter, int *word, char **newtab)//, char *data)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	while (str[i])
	{
		if (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		{
			while (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
				i++;
			if (str[i])
			{
				newtab[*word] = ft_calloc(sizeof(char), *letter + 1);
				if (!newtab)
					return (1);
				// printf("2 : word : %d letter : %d\n", *word, *letter);
				*letter = 0;
				*word += 1;
			}
		}
		if (str[i])
		{
			i++;
			*letter += 1;
		}
	}
	return (0);
}

void	single_quote(char *data, int *letter, int *j)
{
	*letter += 1;
	*j += 1;
	while (data[*j] && data[*j] != '\'')
	{
		*j += 1;
		*letter += 1;
	}
}

void	double_quote(char *data, t_env **env, int *letter, int *j)
{
	*j += 1;
	*letter += 1;
	while (data[*j] && data[*j] != '"')
	{
		if (data[*j] == '$')
		{
			*j += 1;
			letter_env_quote(search_env((data + *j), env), letter);
			while (data[*j] && data[*j] != '$' && data[*j] != '"'
				&& data[*j] != '\'' && data[*j] != ' '
				&& (data[*j] < '\t' || data[*j] > '\r'))
				*j += 1;
		}
		else if (data[*j])
		{
			*j += 1;
			*letter += 1;
		}
	}
}

void	nb_letter(char **data, t_env **env, char **newtab, int word, int fd)
{
	int		letter;
	int		i;
	int		j;

	i = 0;
	while (data[i])
	{
		j = 0;
		letter = 0;
		while (data[i][j])
		{
			if (data[i][j] == '\'')
				single_quote(data[i], &letter, &j);
			if (data[i][j] == '"')
				double_quote(data[i], env, &letter, &j);
			if (data[i][j] && data[i][j] == '$')
			{
				j++;
				if (nb_letter_env(search_env(data[i] + j, env), &letter, &word, newtab))
					return (free_dtab(newtab));
				while (data[i][j] && data[i][j] != '$'
					&& data[i][j] != '"' && data[i][j] != '\'')
					j++;
			}
			else if (data[i][j])
			{
				j++;
				letter++;
			}
		}
		dprintf(fd, "word : %d letter : %d\n", word, letter);
	// 	newtab[word] = ft_calloc(sizeof(char), letter + 1);
	// 	if (!newtab)
	// 		return (free_dtab(newtab), 1);
	// 	// ft_fill(newtab[word], data[i], letter);
		i++;
		word++;
	}
}

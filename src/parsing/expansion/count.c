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
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i])
	{
		*letter += 1;
		i++;
	}
}

void	nb_letter_env(char *str, int *letter, int *word, char **newtab)
{
	int	i;

	i = 0;
	(void)newtab;
	if (!str)
		return ;
	printf("str : %s\n", str);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i])
	{
		if (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		{
			printf("2 : word : %d letter : %d\n", *word, *letter);
			while (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
				i++;
			// newtab[*word] = ft_calloc(sizeof(char), letter + 1);
			// if (!newtab)
			// 	return (1);
			// ft_fill();
			if (str[i])
			{
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
	printf("3 : word : %d letter : %d\n", *word, *letter);
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
			{
				*i += 1;
				letter_env_quote(search_env((str + *i), env), letter);
				while (str[*i] && str[*i] != '$' && str[*i] != '"'
					&& str[*i] != '\'' && str[*i] != ' '
					&& (str[*i] < '\t' || str[*i] > '\r'))
					*i += 1;
			}
			else if (str[*i])
			{
				printf("str[%d] : %c\n", *i, str[*i]);
				*i += 1;
				*letter += 1;
			}
		}
	}
}

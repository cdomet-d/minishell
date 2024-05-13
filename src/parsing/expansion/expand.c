/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:43:58 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/13 16:31:36 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_copy_env(char *data, char *newtab, t_env **env, size_t *j)
{
	size_t	i;
	char	*str;

	i = 0;
	str = search_env(data, env);
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '"')
				str[i] *= -1;
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

void	ft_copy(char *data, char *newtab, t_env **env, char *status)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '$' && data[i + 1] && (ft_isalpha(data[i + 1])
				|| data[i + 1] == '_' || data[i + 1] == '?'))
		{
			i++;
			if (data[i] && data[i] == '?')
			{
				ft_strlcpy(newtab + j, status, ft_strlen(status) + 1);
				j += ft_strlen(status);
				i++;
			}
			else if (data[i])
				i += ft_copy_env(data + i, newtab, env, &j);
		}
		else if (data[i])
			newtab[j++] = data[i++];
	}
}

static void	nb_letter_env(char *data, t_env **env, size_t *letter, size_t *j)
{
	char	*str;
	size_t	i;

	str = NULL;
	i = 0;
	str = search_env(data + *j, env);
	if (str)
	{
		while (str[i++])
			*letter += 1;
	}
	while (data[*j] && (ft_isalnum(data[*j]) || data[*j] == '_'))
		*j += 1;
}

size_t	nb_letter(char *data, t_env **env, char *status)
{
	size_t	letter;
	size_t	j;

	letter = 0;
	j = 0;
	while (data[j])
	{
		if (data[j] == '$' && data[j + 1] && (ft_isalpha(data[j + 1])
				|| data[j + 1] == '_' || data[j + 1] == '?'))
		{
			j++;
			if (data[j] && data[j] == '?')
				nb_letter_status(&letter, &j, status);
			else
				nb_letter_env(data, env, &letter, &j);
		}
		else if (data[j])
		{
			j++;
			letter++;
		}
	}
	return (letter);
}

char	**expand(char **data, t_env **env, int status)
{
	size_t	word;
	size_t	letter;
	char	**newtab;
	char	*str;

	str = ft_itoa(status);
	if (!str)
		return (print_error(errno, "minishell: parsing"));
	word = ft_arrlen(data);
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (free(str), print_error(errno, "minishell: parsing"));
	word = 0;
	while (data[word])
	{
		letter = nb_letter(data[word], env, str);
		newtab[word] = ft_calloc(sizeof(char), letter + 1);
		if (!newtab[word])
			return (free(str), free_dtab(newtab), print_error(errno, "minishell: parsing"));
		ft_copy(data[word], newtab[word], env, str);
		word++;
	}
	newtab[word] = NULL;
	free(str);
	return (newtab);
}

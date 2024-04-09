/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:08:39 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/09 16:41:24 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_copy(char *data, char *newtab, t_env **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
			ft_copy_env(data + i, newtab, env, &j);
			while (data[i] && data[i] != '$' && data[i] != '\''
				&& data[i] != '"')
				i++;
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

void	in_quotes(char *data, int *j, int *letter)
{
	*j += 1;
	*letter += 1;
	while (data[*j] && data[*j] != '\'')
	{
		*j += 1;
		*letter += 1;
	}
}

int	letters(char *data, t_env **env)
{
	int	letter;
	int	j;

	letter = 0;
	j = 0;
	while (data[j])
	{
		if (data[j] == '\'')
			in_quotes(data, &j, &letter);
		if (data[j] == '$')
		{
			j++;
			count_in_env(search_env(data + j, env), &letter);
			while (data[j] && data[j] != '$' && data[j] != '\''
				&& data[j] != '"')
				j++;
		}
		else if (data[j])
		{
			j++;
			letter++;
		}
	}
	return (letter);
}

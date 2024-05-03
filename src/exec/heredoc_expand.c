/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:48:21 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/03 17:48:23 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	search_dollar_hd(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	heredoc_expand(char **line, t_input *in)
{
	char	*temp;
	int		letter;

	letter = nb_letter(*line, &(in)->env, "130");
	temp = ft_calloc(sizeof(char), letter + 1);
	if (!temp)
		return (print_error(errno, NULL), 1);
	ft_copy(*line, temp, &(in)->env, "130");
	free(*line);
	*line = temp;
	letter = 0;
	while (temp[letter])
	{
		if (temp[letter] < 0)
			*line[letter] = temp[letter] * -1;
		letter++;
	}
	return (0);
}

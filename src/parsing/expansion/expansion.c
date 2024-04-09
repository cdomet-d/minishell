/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:28:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/04 19:47:07 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand(t_input *node, t_env **env, int fd)
{
	char	**newtab;
	char	**temp;
	int		word;

	(void)fd;
	newtab = NULL;
	temp = NULL;
	word = 0;
	temp = nb_word(node->data, env, &word);
	// dprintf(fd, "%d\n", word);
	if (!temp)
		return (1);
	newtab = ft_calloc(sizeof(char *), word + 1);
	if (!newtab)
		return (1);
	newtab = nb_letter(temp, newtab);
	if (!newtab)
		return (1);
	free_dtab(temp);
	temp = node->data;
	node->data = NULL;
	node->data = newtab;
	free_dtab(temp);
	return (0);
}

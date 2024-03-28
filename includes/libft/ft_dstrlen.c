/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:59:54 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/15 11:07:19 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dstrlen(char **s)
{
	size_t	i;

	if (!s)
		return (EXIT_FAILURE);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

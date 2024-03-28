/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:32:10 by cdomet-d          #+#    #+#             */
/*   Updated: 2023/11/23 13:58:54 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = -1;
	if (!size)
		return (ft_strlen(src));
	while (src && src[++i] && i < size - 1)
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}

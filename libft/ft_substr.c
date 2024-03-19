/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:30:23 by cdomet-d          #+#    #+#             */
/*   Updated: 2023/12/26 13:15:47 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		sub_len;
	char		*substr;

	i = 0;
	if (!s || !len || !s[i])
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	sub_len = ft_strlen(s) - start;
	if (sub_len > len)
		sub_len = len;
	substr = ft_calloc(sub_len + 1, sizeof (char));
	if (!substr)
		return (NULL);
	while (s[start] && i < len)
		substr[i++] = s[start++];
	return (substr);
}

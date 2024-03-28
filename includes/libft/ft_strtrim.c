/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:36:50 by cdomet-d          #+#    #+#             */
/*   Updated: 2023/11/23 10:59:46 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	size_t		end;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, (int)s1[i]))
		i++;
	j = ft_strlen(s1);
	while (ft_strchr(set, (int)s1[j]))
		j--;
	end = j - i + 1;
	return (ft_substr(s1, i, end));
}

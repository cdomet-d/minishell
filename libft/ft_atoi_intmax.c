/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_intmax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:18:19 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/01/15 11:41:48 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static size_t	ft_skip_space(char *str)
{
	size_t	i;

	i = 0;
	while ((str[i] && str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	return (i);
}

static int	ft_issign(char *str, int i)
{
	int	sign;

	sign = 1;
	if (str[i] == '-')
		return (-sign);
	else
		return (sign);
}

long	ft_atoi_intmax(char *nptr)
{
	int			sign;
	long		nbr;
	size_t		i;

	nbr = 0;
	if (!nptr)
		return (1);
	i = ft_skip_space(nptr);
	sign = ft_issign(nptr, i);
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		if (nbr >= INT_MAX || nbr <= INT_MIN)
			return (nbr * sign);
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	return (nbr * sign);
}

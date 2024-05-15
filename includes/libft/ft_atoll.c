/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:23:09 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/14 13:41:49 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

unsigned long long int	ft_atoll(char *nptr)
{
	size_t		i;
	int			sign;
	unsigned long long int	nbr;

	nbr = 0;
	if (!nptr)
		return (1);
	i = ft_skip_space(nptr);
	sign = ft_issign(nptr, i);
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		// if (((nbr * 10 + nptr[i] - '0') / 10 != nbr))
		// {
		// 	if (sign < 0)
		// 		return ((int)LONG_MIN);
		// 	else
		// 		return ((int)LONG_MAX);
		// }
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	return (nbr * sign);
}
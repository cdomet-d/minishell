/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:52:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/27 09:58:19 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char    **keep_split(char *str, char sep)
{
    size_t  i;

    i = 0;
    if (!str || !sep)
        return (NULL);
    while (str[i] != sep)
    
}

size_t  count_sep(char *str, char sep)
{
    size_t  i;
    size_t  csep;

    csep = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == sep)
            csep++;
    }
}
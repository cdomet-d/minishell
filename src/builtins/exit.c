/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:54:27 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/10 13:01:35 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	mh_exit(char *line, t_input *in)
{
	int	rv;

	if (in && in->data[1])
		rv = ft_atoi(in->data[1]);
	else
		rv = in->status;
	if (line)
		free(line);
	fatal_exit(&in, rv, "exit");
}

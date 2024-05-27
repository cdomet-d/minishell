/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:14:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/24 12:03:51 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*heredoc_error(t_input	*in, char *tmpdel, char *line, bool err)
{
	if (in->data[0][0] < 0)
		in->data[0][0] *= -1;
	if (err)
	{
		if (errno == ENOMEM)
			print_error(errno, "minishell");
		verror \
			("minishell: ", "warning: expected delimiter: ", in->data[0]);
	}
	free(tmpdel);
	free(line);
	return (NULL);
}

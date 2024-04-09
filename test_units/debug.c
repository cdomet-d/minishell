/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:35:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/07 22:06:53 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	main(int argc, char **argv)
{
	t_input	*in;

	in = NULL;
	(void)argc;
	init_input(argv, &in, NULL);
	print_in_for(in);
	in = in->next->next->next;
	if (is_first_pipe(in))
		printf("First pipe");
	else
		printf("Not first pipe");
}

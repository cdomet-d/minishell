/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:15:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/30 17:56:15 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int get_nonull(void)
{
	return (1);
}

void	sighandler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
		rl_done = g_sig;
	else
		printf("signal received : %d\n", sig);
}

void	sigend(void)
{
	g_sig = 0;
}

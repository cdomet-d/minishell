/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:15:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/08 19:19:12 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_nonull(void)
{
	return (1);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = sig;
		rl_done = g_sig;
		return ;
	}
	else
		printf("signal received : %d\n", sig);
}

void	sigend(void)
{
	g_sig = -1;
}

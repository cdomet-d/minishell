/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:15:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/15 16:09:27 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_nonull(void)
{
	return (1);
}

void	sighandle_child(int sig)
{
	fprintf(stderr, "sig : %d\n", sig);
	fprintf(stderr, "g_sig : %d\n", g_sig);
	g_sig = sig;
	return ;

}

static void	sighandler(int sig)
{
	g_sig = sig;
	rl_done = g_sig;
	return ;
}

void	sigend(void)
{
	g_sig = -1;
}

void	siglisten(void)
{
	rl_event_hook = get_nonull;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

char	*send_eof(char *line)
{
	if (!line)
		return (NULL);
	return (line);
}

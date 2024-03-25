/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:33:33 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/25 18:11:16 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_HEADER_H
# define EXEC_HEADER_H

# include "minishell.h"

typedef struct s_redir
{
	int	pip;
	int	inredir;
	int	outredir;
}	t_redir;

/* local file for exec debug */
void	init_input(char *argv[], t_input **input, t_env *env);
void	init_env(char **envp, t_env **env);
int		token(char *str);

/* exec && exec utils */
void	print_redirs(t_input *input);
void	count_pipes(t_input *in, t_redir *redir);
void	count_redirs(t_input *in, t_redir *redir);



#endif

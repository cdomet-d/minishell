/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:39:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/29 15:04:44 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <sys/types.h> // open
# include <sys/stat.h> // open
# include <fcntl.h> // open

# define R 0
# define W 1

# define SUCCESS 1

/*------------------------------- EXEC STRUCTS -------------------------------*/

typedef struct s_redir
{
	int	pip;
	int	inredir;
	int	outredir;
}	t_op;

typedef struct s_fd
{
	int	pfd[2];
	int	ffd;
	int	pid;
	int	tmpin;
}	t_fd;

/*------------------------------ EXEC FUNCTIONS ------------------------------*/

/* local file for exec debug */
void	init_input(char *argv[], t_input **input, t_env *env);
void	init_env(char **envp, t_env **env);
int		token(char *str);

/* exec && exec utils */
void	print_ops(t_op count);
void	check_redirs(t_input *in, t_op *counter);
void	count_brackets(t_input *in, t_op *counter);
void	*exec_cmd(t_input *in);
void	init_fd(t_fd *fd);
void	print_fds(t_fd *fd);

/*--------------------------------- BUILTINS ---------------------------------*/

/* builtins utils */
char	*split_wsep(char *str, char sep);

/* builtins */
void	unset(t_env **env, char *key);
void	*export(t_env *env, char *var);
void	mh_exit(char *line, t_input *in, t_env *env);

/*----------------------------------------------------------------------------*/

#endif
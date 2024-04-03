/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:39:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/03 16:21:49 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <sys/types.h> // open
# include <sys/stat.h> // open
# include <fcntl.h> // open
# include <sys/types.h> // waitpid
# include <sys/wait.h> // waitpid

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

	/* exec */
void	*exec_cmd(t_input *in);

	/* exec utils */
bool	op_true(t_input *in, t_tok op);
bool	pipe_true(t_input *in);

//converts env->env to char **
char	**arenvlst(t_env	*env);
t_input	*find_redir(t_input	*in, t_tok op);
void	init_fd(t_fd *fd);


	/* redirections */
void	*pip_redir(t_fd *fd);
void	*in_redir(t_fd *fd, t_input *in);
void	*out_redir(t_fd *fd, t_input *in);

/*--------------------------------- BUILTINS ---------------------------------*/

	/* builtins utils */
char	*split_wsep(char *str, char sep);

	/* builtins */
void	unset(t_env **env, char *key);
void	*export(t_env *env, char *var);
void	mh_exit(char *line, t_input *in, t_env *env);

/*--------------------------------- DISPLAYS ---------------------------------*/
void	print_ops(t_op count);
void	print_fds(t_fd *fd);
void	print_in_node(t_input *node);
/*----------------------------------------------------------------------------*/

#endif
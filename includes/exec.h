/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:39:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/22 17:32:33 by cdomet-d         ###   ########lyon.fr   */
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
# define EXE_ERR 1
# define EXE_OK 0

/*------------------------------- EXEC STRUCTS -------------------------------*/

typedef struct s_redir
{
	int	pip;
	int	inredir;
	int	outredir;
}	t_op;

typedef struct s_fd
{
	int		pfd[2];
	int		hfd;
	int		ffd;
	int		pid;
	int		tmpin;
	size_t	pnb;
}	t_fd;

/*------------------------------ EXEC FUNCTIONS ------------------------------*/

	/* exec */
void	*exec_cmd(t_input *in);

	/* error_handling */
void	*exe_failure(t_fd *fd, t_input *in, char **arenv);

	/* arenvlst */
char	**arenvlst(t_env	*env);

	/* fd_handling */
void	close_pfd(t_fd *fd);
void	close_pipe_read(t_fd *fd);
void	close_pipe_write(t_fd *fd);
void	init_fds(t_fd *fd);

	/* operators utils */
bool	op_true(t_input *in, t_tok op);
size_t	count_pipes(t_input *in);
t_input	*find_next_pipe(t_input	*in, t_fd *fd);
t_input	*find_tok(t_input	*in, t_tok op, bool next);

	/* builtins_exec */
int builtin_true(t_input *in);
void exec_builtin(t_input **in);

	/* redirections utils */
bool	is_first(t_input *in, t_tok token);
bool	is_last(t_input *in, t_tok token);

	/* exec_utils */
void	*save_pipin(t_fd *fd);
void	*create_child(t_input *in, t_fd *fd);
void	wait_for_children(void);


	/* redirections */
void	*app_redir(t_fd *fd, t_input *in);
void	*in_redir(t_fd *fd, t_input *in);
void	*out_redir(t_fd *fd, t_input *in);
void	*pip_redir(t_input *tmp, t_fd *fd);

	/* heredoc */
void	*create_hdocs(t_fd *fd, t_input *in);

/*--------------------------------- BUILTINS ---------------------------------*/

	/* builtins utils */
char	*split_wsep(char *str, char sep);
void	*env_rmone(t_env **sup, t_env *head);

	/* builtins */
int		echo(char **data);
int		env(t_input *node);
int		pwd(char **data);
void	*export(t_input **in, char *var);
void	*unset(t_env **env, char *key);
void	mh_exit(char *line, t_input *in, t_env *env);

/*--------------------------------- DISPLAYS ---------------------------------*/
void	print_ops(t_op count);
void	print_fds(t_fd *fd);
void	print_in_node(t_input *node, t_fd *fd, char *str);
void	pmin(t_input *input, char *str);
void	print_enum(int token);

/*----------------------------------------------------------------------------*/

#endif
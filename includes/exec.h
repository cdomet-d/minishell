/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:39:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/26 15:43:13 by csweetin         ###   ########.fr       */
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
// error_handling ------------

/* exec_errors.c */
void	*exe_failure(t_fd *fd, t_input *in);

// utils ---------------------

/* arenvlst.c */
char	**arenvlst(t_env	*env);

/* fd_handling.c */
void	init_fds(t_fd *fd, t_input *in);
void	close_pipe_read(t_fd *fd);
void	close_pipe_write(t_fd *fd);
void	close_pfd(t_fd *fd);
void	reset_stds(int tmpstdin, int tmpstdout);

/* exec_utils.c */
void	close_and_wait(t_input *in, t_fd *fd);
void	*create_child(t_input *in, t_fd *fd);
void	*save_pipin(t_fd *fd);

/* operators_utils.c */
size_t	count_pipes(t_input *in);
bool	op_true(t_input *in, t_tok op);
t_input	*find_tok(t_input	*in, t_tok op, bool next);
t_input	*find_next_pipe(t_input	*in, t_fd *fd);

/* redirection_utils.c */
bool	is_first(t_input *in);
bool	is_last(t_input *in);

/* buitin_utils.c */
t_tok	builtin_true(t_input *in);
void	exec_exit_inpipe(t_fd *fd, t_input *in, t_input *tmp);

// exec ----------------------

/* heredoc.c */
void	*create_hdocs(t_fd *fd, t_input *in);

/* heredoc_expand.c */
int		heredoc_expand(char **line, t_input *in);
int		search_dollar_hd(char *line);

/* redirections.c */
void	*out_redir(t_fd *fd, t_input *in);
void	*app_redir(t_fd *fd, t_input *in);
void	*in_redir(t_fd *fd, t_input *in);
void	*pip_redir(t_input *tmp, t_fd *fd);

/* exec.c */
void	*exec_cmd(t_input *in);

/* exec_builtins.c */
void	exec_builtin(t_input **in);
void	*redir_builtins(t_fd *fd, t_input *tmp);
void	*handle_bt_nopipe(t_fd *fd, t_input	*in, t_input *tmp);

/*--------------------------------- BUILTINS ---------------------------------*/

// builtins ------------------

/* unset.c */
void	*unset(t_env **env, char *key);

/* builtin_utils.c */
char	*split_wsep(char *str, char sep);
void	*env_rmone(t_env **sup, t_env *head);

/* exit.c */
void	mh_exit(char *line, t_input *in, t_env **env);

/* export.c */
void	*export(t_input **in);
void	*exprt_inenv(t_env **env, char *data);

/* env.c */
void	*env(t_input *node);

/* echo.c */
int		echo(char **data);

/* pwd.c */
int		pwd(char **data);

/* cd.c */
int 	cd(t_input **in);
int		check_directory(char *var);
char	*find_var_env(t_env *env, char *var);
int		change_pwd(t_env **env, char *path, char *var);

/*--------------------------------- DISPLAYS ---------------------------------*/
void	print_ops(t_op count);
void	print_fds(t_fd *fd);
void	print_in_node(t_input *node, t_fd *fd, char *str);
void	pmin(t_input *input, char *str);
void	print_enum(int token);

/*----------------------------------------------------------------------------*/

#endif
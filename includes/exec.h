/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:39:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/02 16:10:39 by cdomet-d         ###   ########lyon.fr   */
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
# include <signal.h> // signals


# define R 0
# define W 1

# define SUCCESS 1
# define EXE_ERR 1
# define EXE_OK 0

/*------------------------------ EXEC FUNCTIONS ------------------------------*/
// error_handling ------------

/* exec_errors.c */
void	*exe_failure(t_fd *fd, t_input *in);

// utils ---------------------

/* arenvlst.c */
char	**arenvlst(t_env	*env);

/* buitin_utils.c */
t_tok	builtin_true(t_input *in);

/* exec_utils.c */
void	close_and_wait(t_input *in, t_fd *fd);
void	*create_child(t_input *in, t_fd *fd);
void	*save_pipin(t_fd *fd);

/* fd_handling.c */
void	close_pfd(t_fd *fd);
void	close_pipe_read(t_fd *fd);
void	close_pipe_write(t_fd *fd);
void	init_fds(t_fd *fd, t_input *in);
void	reset_stds(int tmpstdin, int tmpstdout);

/* heredoc_utils.c */
bool	here_true(t_input *in);
t_input	*find_here(t_input	*in, bool next);

/* operators_utils.c */
bool	op_true(t_input *in, t_tok op);
size_t	count_pipes(t_input *in);
t_input	*find_next_pipe(t_input	*in, t_fd *fd);
t_input	*find_tok(t_input	*in, t_tok op, bool next);

/* redirection_utils.c */
bool	is_first(t_input *in);
bool	is_last(t_input *in);
void	*open_infiles(t_fd *fd, t_input *tmp);

/* heredoc_expand.c */
int		search_dollar_hd(char *line);
int		heredoc_expand(char **line, t_input *in);

// exec ----------------------

/* exec.c */
void	*exec_cmd(t_input *in);

/* redirections.c */
void	*out_redir(t_fd *fd, t_input *in);
void	*app_redir(t_fd *fd, t_input *in);
void	*in_redir(t_fd *fd, t_input *in);
void	*pip_redir(t_input *tmp, t_fd *fd);
void	*here_redir(t_fd *fd, t_input *in);

/* exec_builtins.c */
void	exec_builtin(t_input **in);
void	*redir_builtins(t_fd *fd, t_input *tmp);
void	*handle_bt_nopipe(t_fd *fd, t_input	*in, t_input *tmp);

/* heredoc.c */
void	*create_hdocs(t_fd *fd, t_input *in);

// signals -------------------

/* sighandler.c */
void	sighandler(int sig);
int		get_nonull(void);
void	sigend(void);

/*----------------------------------------------------------------------------*/

#endif
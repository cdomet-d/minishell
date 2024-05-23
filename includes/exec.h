/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:39:49 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/22 13:11:54 by cdomet-d         ###   ########lyon.fr   */
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

// exec ----------------------
/* exec.c */
void	*exec_cmd(t_input *in);

/* redirections.c */
void	*redir_all_in_pipe(t_fd *fd, t_input *in);
void	*pip_redir(t_input *tmp, t_fd *fd);

/* exec_errors.c */
void	*killchild(t_fd *fd, t_input *in);
void	display_exec_error(t_input *in);

// exec_utils ---------------------

/* arenvlst.c */
char	**arenvlst(t_env	*env);

/* fd_handling.c */
void	init_fds(t_fd *fd, t_input *in);
void	close_pipe_read(t_fd *fd);
void	close_pipe_write(t_fd *fd);
void	close_pfd(t_fd *fd);
void	reset_stds(int tmpstdin, int tmpstdout);

/* exec_utils.c */
void	init_exec(t_input *in, t_input **tmp, t_fd *fd);
t_input	*get_last_node(t_input *in);
void	close_and_wait(t_input *in, t_fd *fd);
void	*create_child(t_fd *fd);
void	*save_pipin(t_fd *fd);

/* operators_utils.c */
size_t	count_pipes(t_input *in);
bool	op_true(t_input *in, t_tok op);
t_input	*find_tok(t_input	*in, t_tok op, bool next);
t_input	*find_next_pipe(t_input	*in, t_fd *fd);
t_input	*find_prev_tok(t_input	*in, t_tok op);

/* redirection_utils.c */
bool	is_first(t_input *in);
bool	is_last(t_input *in);
void	*open_infiles(t_fd *fd, t_input *tmp);
void	*open_outfiles(t_fd *fd, t_input *tmp);

// heredoc -------------------

/* heredoc.c */
void	*create_hdocs(t_fd *fd, t_input *in);

/* heredoc_expand.c */
int		search_dollar_hd(char *line);
int		heredoc_expand(char **line, t_input *in);

/* heredoc_utils.c */
bool	here_true(t_input *in);
t_input	*find_here(t_input	*in, bool next);
char	*get_delim(t_input *in);
bool	exit_loop(char *line, char *tmpdel, t_input	*in);

/* heredoc_errors.c */
void	*heredoc_error(t_input	*in, char *tmpdel, char *line, bool err);

// signals -------------------

/* sig_set_stat.c */
void	set_status(t_input *in, int e_stat);

/* sighandler.c */
int		get_nonull(void);
void	sigend(void);
void	siglisten(void);
char	*send_eof(char *line);
void	sighandler(int sig);

#endif
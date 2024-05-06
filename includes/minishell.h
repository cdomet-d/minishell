/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/03 14:45:11 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h> // strerror
# include <errno.h> // errno
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <linux/limits.h>

extern int 	g_sig;

/*----------------------------- STRUCTURES ----------------------------*/

typedef enum e_enum
{
	pip, // |
	inredir, // <
	outredir, // >
	append, // >>
	heredoc, // <<
	command,
	ms_echo,
	ms_cd,
	ms_pwd,
	ms_export,
	ms_unset,
	ms_env,
	ms_exit,
}	t_tok;

typedef struct s_env
{
	char			*env;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_input
{
	char			**data;
	t_tok			tok;
	t_env			*env;
	struct s_input	*next;
	struct s_input	*prev;
	int				status;
}	t_input;

typedef struct s_fd
{
	int		pfd[2];
	int		hfd;
	int		ffd;
	int		pid;
	int		tmpin;
	size_t	pnb;
}	t_fd;

/*----------------------------- COMMON FUNCTIONS -----------------------------*/

// lst_utils -----------------

/* input_lst_utils.c */
void	input_freelst(t_input **lst);
void	input_addback(t_input **lst, t_input *node);
t_input	*input_newnode(char **data, int token, t_env *env);

/* env_lst_utils.c */
void	env_freelst(t_env **env);
void	env_addback(t_env **env, t_env *node);
t_env	*env_newnode(char *data);

// utils ---------------------

/* display_data.c */
void	print_fds(t_fd *fd);

/* display_structs_v.c */
void	print_in_for(t_input *input);
void	print_enum(int token);
void	print_in_node(t_input *node, t_fd *fd, char *str);
void	print_env_for(t_env *env, char *str);
void	vdisplay_dtab(char **dtab);

/* display_structs_q.c */
void	pmin(t_input *input, char *str);
void	display_dtab(char **dtab);

/* error_handling.c */
void	fatal_exit(t_input **lst, int error_code, char *error_message);
void	free_env(t_env *lst, int error_code, char *error_message);
void	*print_error(int error_code, char *error_message);

// builtins ------------------

/* builtin_utils.c */
char	*split_wsep(char *str, char sep);
char	*find_var_env(t_env *env, char *var);
void	*exprt_inenv(t_env **env, char *data);
// t_env	**env_rmone(t_env **sup, t_env **head);

/* echo.c */
int		cmp_opt(char *arg);
int		echo(char **data);

/* env.c */
void	*env(t_input *node);

/* exit.c */
void	mh_exit(char *line, t_input *in, t_env **env);

/* pwd.c */
int		pwd(t_env *env, char **data);

/* export.c */
int		check_arg(char *var);
int		change_var(t_input **in, char *var);
void	*export(t_input **in);

/* export_utils.c */
void	*sort_env(t_env	*env);

/* cd.c */
int		cd(t_input *in);

/* cd_utils.c */
int		check_directory(char *var, char *path);
int		pwds(t_input *in, char *path);
char	*make_path(char *tab, char *path, char **temp);
// char	*check_len(char	*path, t_env *env);

/* unset.c */
t_env	**unset(t_env **env, char **key);

/*----------------------------------------------------------------------------*/

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:41:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/22 15:28:31 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "exec.h"

/*----------------------------- PARSING -----------------------------*/

/* parsing.c */
void	parsing(t_input **input, t_env **env, char *line, int *status);
void	revert(t_input *node);

/* rm_quotes.c */
int		search_quotes(t_input *node);

/* toke_builtin.c */
void	find_builtin(t_input *node);

/* create_lst.c */
void	create_env(t_input **input, char **envp, t_env **env);
int		create_input(t_input **input, t_env **env, char **data, int tok);

/* cmd_path.c */
int		cmd_path(t_input *input, t_env **env);
int		path_slash(char *cmd);

/* cmd_path_utils.c */
size_t	path_len(char *env, size_t *i);
int		check_path(char **path);

/* tokenization.c */
int		tokenization(t_input **input, t_env **env, char *line, int *status);

/* toke_type.c */
int		tok_inredir(t_input **input, t_env **env, char *line, size_t *i);
int		tok_outredir(t_input **input, t_env **env, char *line, size_t *i);
int		tok_command(t_input **input, t_env **env, char *line, size_t *i);
int		tok_pipe(t_input **input, t_env **env, char *line, size_t *i);

/* tokenization_utils.c */
int		check_quote(char *line);
char	**get_data(t_input **input, char *line, size_t *i, int *rv);

/* create_data.c */
void	count_word(char *line, size_t i, size_t *word);
char	**build_tab(char *line, size_t *i, size_t word);

/* cmd_opt.c */
int		check_opt(t_input **input, char *line, size_t *i);

/* expand_split.c */
char	**expand_split(char **data, t_env **env, int status);

/* expand.c */
char	**expand(char **data, t_env **env, int status);
void	ft_copy(char *data, char *newtab, t_env **env, char *status);
size_t	nb_letter(char *data, t_env **env, char *status);

/* expand_utils.c */
int		search_dollar(char **data);
char	*search_env(char *data, t_env **env);
void	nb_letter_status(size_t *letter, size_t *j, char *status);

/* expand_split_utils.c */
void	put_in_neg(char *data, char quote1, char quote2);
int		check_ws(char **tab);

/*----------------------------------------------------------------------*/

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:41:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/23 19:28:31 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "exec.h"

/*----------------------------- PARSING -----------------------------*/

void	parsing(t_input **input, t_env **env, char *line, int rv);
void	init_all(char **str, char **envp, t_env **env, t_input **input);
void	process_line(char *line, t_input *input, t_env *env);
int		cmd_path(t_input *input, t_env **env);
int		path_len(char *env, int *i);
int		check_path(char **path);
char	*rm_quotes(char *str);
void	find_builtin(t_input *node);
void	revert(t_input *node);

/*----------------------------TOKENIZATION ---------------------------*/

int		tokenization(t_input **input, t_env **env, char *line);
int		tok_inredir(t_input **input, t_env **env, char *line, int *i);
int		tok_outredir(t_input **input, t_env **env, char *line, int *i);
int		tok_command(t_input **input, t_env **env, char *line, int *i);
int		tok_pipe(t_input **input, t_env **env, char *line, int *i);

/* tokenization utils */
int		check_quote(char *line);
void	count_word(char *line, int i, int *word);
char	**get_data(t_input **input, char *line, int *i);
char	**build_tab(char *line, int *i, int word);
int		check_opt(t_input **input, char *line, int *i);

/*----------------------------- EXPANSION -----------------------------*/

char	**expand_split(char **data, t_env **env, int rv);
char	**expand(char **data, t_env **env, int rv);

/* expand utils */
int		search_dollar(char **data);
char	*search_env(char *data, t_env **env);
int		ft_strcmp(char *data, char *env);
void	put_in_neg(char *data, char quote1, char quote2);
int		check_ws(char **tab);

/*---------------------------- CREATE LISTS ----------------------------*/

void	create_env(t_input **input, char **envp, t_env **env);
int		create_input(t_input **input, t_env **env, char **data, int tok);

/*----------------------------------------------------------------------*/

#endif
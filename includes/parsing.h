/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:41:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/05/03 18:26:49 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "exec.h"

/*----------------------------- PARSING -----------------------------*/

void	parsing(t_input **input, t_env **env, char *line, int rv);
char	*rm_quotes(char *str);
void	find_builtin(t_input *node);
void	revert(t_input *node);

/* create_lst */
void	create_env(t_input **input, char **envp, t_env **env);
int		create_input(t_input **input, t_env **env, char **data, int tok);

/* cmd_path */
int		cmd_path(t_input *input, t_env **env);

/* cmd_path_utils */
int		path_len(char *env, int *i);
int		check_path(char **path);

/* tokenization */
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

/* expansion */
char	**expand_split(char **data, t_env **env, int rv);
char	**expand(char **data, t_env **env, int rv);
void	ft_copy(char *data, char *newtab, t_env **env, char *rv);
int		nb_letter(char *data, t_env **env, char *rv);

/* expansion utils */
int		search_dollar(char **data);
char	*search_env(char *data, t_env **env);
int		ft_strcmp(char *data, char *env);
void	put_in_neg(char *data, char quote1, char quote2);
int		check_ws(char **tab);
void	nb_letter_rv(int *letter, int *j, char *rv);

/*----------------------------------------------------------------------*/

#endif
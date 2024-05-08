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

/* parsing.c */
void	parsing(t_input **input, t_env **env, char *line, int rv);
void	revert(t_input *node);

/* rm_quotes.c */
char	*rm_quotes(char *str);

/* toke_builtin.c */
void	find_builtin(t_input *node);

/* create_lst.c */
void	create_env(t_input **input, char **envp, t_env **env);
int		create_input(t_input **input, t_env **env, char **data, int tok);

/* cmd_path.c */
int		cmd_path(t_input *input, t_env **env);

/* cmd_path_utils.c */
size_t	path_len(char *env, size_t *i);
int		check_path(char **path);

/* tokenization.c */
int		tokenization(t_input **input, t_env **env, char *line);

/* toke_type.c */
int		tok_inredir(t_input **input, t_env **env, char *line, size_t *i);
int		tok_outredir(t_input **input, t_env **env, char *line, size_t *i);
int		tok_command(t_input **input, t_env **env, char *line, size_t *i);
int		tok_pipe(t_input **input, t_env **env, char *line, size_t *i);

/* tokenization_utils.c */
int		check_quote(char *line);
char	**get_data(t_input **input, char *line, size_t *i);

/* create_data.c */
void	count_word(char *line, size_t i, size_t *word);
char	**build_tab(char *line, size_t *i, size_t word);

/* cmd_opt.c */
int		check_opt(t_input **input, char *line, size_t *i);

/* expand_split.c */
char	**expand_split(char **data, t_env **env, int rv);

/* expand.c */
char	**expand(char **data, t_env **env, int rv);
void	ft_copy(char *data, char *newtab, t_env **env, char *rv);
int		nb_letter(char *data, t_env **env, char *rv);

/* expand_utils.c */
int		search_dollar(char **data);
char	*search_env(char *data, t_env **env);
void	nb_letter_rv(int *letter, int *j, char *rv);

/* expand_split_utils.c */
void	put_in_neg(char *data, char quote1, char quote2);
int		check_ws(char **tab);

/*----------------------------------------------------------------------*/

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:41:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/09 17:46:53 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "exec.h"

/*----------------------------- PARSING -----------------------------*/

void	parsing(t_input **input, t_env **env, char *line);
void	init_all(char **str, char **envp, t_env **env, t_input **input);
void	process_line(char *line, t_input *input, t_env *env);

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

int		expand(t_input *node, t_env **env);
char	**nb_word(char **data, t_env **env, int *word);
char	**nb_letter(char **data, char **newtab);
int		letters(char *data, t_env **env);
void	ft_copy(char *data, char *newtab, t_env **env);

/* expand utils */
int		check_for_dollar(t_input *node);
char	*search_env(char *data, t_env **env);
int		ft_strcmp(char *data, char *env);
// void	revert(char **data);
// char	**tab_dup(char **data);

/*---------------------------- CREATE LISTS ----------------------------*/

void	create_env(t_input **input, char **envp, t_env **env);
int		create_input(t_input **input, t_env **env, char **data, int tok);

/*----------------------------------------------------------------------*/

#endif
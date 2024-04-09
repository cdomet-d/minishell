/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:41:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/04 15:53:04 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "exec.h"

/*----------------------------- PARSING -----------------------------*/

typedef struct s_expand
{
    int     i;
    int     j;
    int     null;
    char    *str;
    char    *tmp;
    char    **save;
    bool    dollar;
} t_exp;

void	parsing(t_input **input, t_env **env, char *line);

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
int	    check_opt(t_input **input, char *line, int *i);

/*----------------------------- EXPANSION -----------------------------*/

int		expand(t_input *node, t_env **env);
char    **nb_word(char **data, /*char **save, */t_env **env, int *word);
char	**ft_replace(char **data, t_env **env);
char 	**nb_letter(char **data, char **newtab);
void	double_quote(char *data, t_env **env, int *letter, int *j);
void	single_quote(char *data, int *letter, int *j);
int 	nb_letter_env(char *str, int *letter, int *word, char **newtab);

/* expand utils */
int		check_for_dollar(t_input *node);
char	*search_env(char *data, t_env **env);
int		ft_strcmp(char *data, char *env);
void	revert(char **data);
char	**tab_dup(char **data);

/*---------------------------- CREATE LISTS ----------------------------*/

void	create_env(t_input **input, char **envp, t_env **env);
int		create_input(t_input **input, t_env **env, char **data, int tok);

/*----------------------------------------------------------------------*/

#endif
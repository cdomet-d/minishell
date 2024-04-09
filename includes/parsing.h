/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/09 17:04:44 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "exec.h"

void	parsing(t_input **input, t_env **env, char *line);
void	expand(t_input *node, t_env **env);
void	create_env(t_input **input, char **envp, t_env **env);
void	count_word(char *line, int i, int *word);
char	**build_tab(char *line, int *i, int word);
char	**get_data(t_input **input, char *line, int *i);
int		create_input(t_input **input, t_env **env, char **data, int tok);
int		tokenization(t_input **input, t_env **env, char *line);
int		check_quote(char *line);
int		check_for_dollar(t_input *node);
int		tok_inredir(t_input **input, t_env **env, char *line, int *i);
int		tok_outredir(t_input **input, t_env **env, char *line, int *i);
int		tok_command(t_input **input, t_env **env, char *line, int *i);
int		tok_pipe(t_input **input, t_env **env, char *line, int *i);
void	init_all(char **str, char **envp, t_env **env, t_input **input);
void	process_line(char *line, t_input *input, t_env *env);

#endif
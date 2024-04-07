/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:41:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/04/07 22:27:39 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "exec.h"

void	parsing(t_input **input, t_env **env, char *line);
void	*tokenization(t_input **input, t_env **env, char *line);
void	expand(t_input **input, t_env **env);
void	create_env(t_input **input, char **envp, t_env **env);
void	create_input(t_input **input, t_env **env, char **data, int tok);
char	**build_tab(char *line, int *i, int word);
int		check_quote(char *line);
char	**get_data(t_input **input, char *line, int *i);
void	count_word(char *line, int i, int *word);
void	init_all(char **str, char **envp, t_env **env, t_input **input);
void	process_line(char *line, t_input *input, t_env *env);

#endif
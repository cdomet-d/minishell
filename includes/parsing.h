/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:41:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/28 18:29:47 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void	parsing(t_input **input, t_env **env, char *line);
void	tokenization(t_input **input, t_env **env, char *line);
void	expand(t_input *node, t_env **env);
void	create_env(t_input **input, char **envp, t_env **env);
void	create_input(t_input **input, t_env **env, char **data, int tok);
void	count_word(char *line, int i, int *word);
char	**build_tab(char *line, int *i, int word);
char	**get_data(t_input **input, char *line, int *i);
int		check_quote(char *line);
int	    check_for_dollar(t_input *node);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:41:26 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/28 17:38:03 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void	create_env(t_input **input, char **envp, t_env **env);
void	tokenization(t_input **input, t_env **env, char *line);
void	create_input(t_input **input, t_env **env, char **data, int tok);
char	**build_tab(char *line, int *i, int word);
int		check_quote(char *line);
char	**get_data(t_input **input, char *line, int *i);
void	count_word(char *line, int i, int *word);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/25 14:37:44 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h> // strerror
# include <errno.h> // errno
# include "libft/libft.h"

typedef enum s_enum
{
	pip, // |
	in_bracket, // <
	out_bracket, // >
	append_bracket, // >>
	heredoc, // <<
	command,
	file,
	delimiter,
}	t_tok;

typedef struct s_env
{
	char			*env;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_input
{
	char			**data;
	t_tok			tok;
	t_env			*env;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

/* env list utils*/
t_env	*env_newnode(char *data);
void	env_addback(t_env **env, t_env *node);
void	env_freelst(t_env *env);
void	init_env(char **envp, t_env **env);

/* input list utils */
t_input	*input_newnode(char **data, int token, t_env *env);
void	input_addback(t_input **lst, t_input *node);
void	input_freelst(t_input **lst);

/* display */
t_env	*env_last(t_env	*env);
void	print_env_for(t_env *env);
void	print_env_back(t_env *env);
void	display_dtab(char **dtab);
void	print_in_for(t_input *input);

/* error handling */
void	free_all(t_input **lst, int error_code, char *error_message);
void	free_env(t_env *lst, int error_code, char *error_message);
void	print_error(int error_code, char *error_message);

/* local file for exec debug */
void	init_input(char *argv[], t_input **input, t_env *env);
void	init_env(char **envp, t_env **env);
int	token(char *str);

#endif
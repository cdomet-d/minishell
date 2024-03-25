/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 20:12:01 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
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
t_env	*env_newnode(t_input *input, char *data);
void	env_addback(t_env **env, t_env *node);
void	env_freelst(t_env *env);

/* input list utils */
t_input	*input_newnode(char **data, int token, t_env *env);
void	input_addback(t_input **lst, t_input *node);
void	input_freelst(t_input **lst);

/* display */
t_env	*env_last(t_env	*env);
void	print_env_for(t_env *env);
void	print_env_back(t_env *env);

/* error handling */
void	free_all(t_input **lst, char **env);

#endif
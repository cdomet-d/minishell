/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 17:59:29 by cdomet-d         ###   ########lyon.fr   */
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
t_env	*env_last(t_env	*env);
t_env	*env_newnode(t_input *input, char *data);
void	env_addback(t_env **env, t_env *node);
void	env_freelst(t_env *env);

/* input list utils */
t_input	*input_newnode(char **data, int token, t_env *env);
void	input_addback(t_input **lst, t_input *node);
void	input_freelst(t_input **lst);

/* display */
void	print_env_for(t_env *env);
void	print_env_back(t_env *env);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/22 14:48:50 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft/libft.h"

typedef enum s_enum
{
	piping, // |
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
	bool			done;
	t_tok			tok;
	t_env			env;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

/* env list utils*/
t_env	*env_add_back(t_env **env, t_env *new);
t_env	*env_create_node(t_input *input, char *data);
t_env	*env_last(t_env	*env);
void	env_free_lst(t_env *env);

/* display */
void	print_env_for(t_env *env);
void	print_env_back(t_env *env);

#endif
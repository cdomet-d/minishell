/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:47:16 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/22 17:13:37 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdio.h>

typedef enum s_enum
{
	pipe, // |
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
	char	*env;
}	t_env;

typedef struct s_input
{
	char			**data;
	t_env			*env;
	t_tok			tok;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

t_input	*input_newnode(char **data, int token, t_env *env);
void	input_addback(t_input **lst, t_input *new);
void	input_lstfree(t_input **lst);

#endif
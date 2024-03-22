/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:47:16 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/22 14:20:59 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>

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

t_input	*create_node(char **data, t_tok token, t_env **env);

#endif
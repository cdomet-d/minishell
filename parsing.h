//HEADER

#ifndef PARSING_H
# define PARSING_H

#include <stdlib.h>

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

typedef struct s_input
{
    char            **data;
	t_env           *env;
	t_tok			tok;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

typedef struct s_env
{
    char *env;
} t_env;

t_input	*create_node(char **data, t_tok token, t_env *env);

#endif
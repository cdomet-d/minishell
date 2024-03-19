/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/19 12:37:42 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_enum
{
	pipe, // |
	in_bracket, // <
	out_bracket, // >
	heredoc, // <<
	append_bracket, // >>
	command,
}	t_token;

typedef struct s_list
{
	t_token			token;
	char			*litteral;
	char			*path;
	char			**arg;
	char			**env;
	struct s_list	*next;
}	t_list;

// default structure for commands, to give to execve
typedef	struct s_cmd
{
	char			*path;
	char			**arg;
	char			**env;
}	t_cmd;

// structure for operators found with the type of operators
typedef struct s_operator
{
	t_token	token;
	char	*file;
	t_cmd	cmd1;
	t_cmd	cmd2;
}	t_op;

/*


*/
#endif


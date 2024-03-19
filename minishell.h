/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:14 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/19 13:52:55 by csweetin         ###   ########.fr       */
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

/*
typedef	struct s_cmd
{
	t_op			op;
	char			*path;
	char			**arg;
	char			**env;
}	t_cmd;

typedef struct s_operator
{
	t_token	token;
	char	*file;
}	t_op;

typedef struct s_pipe
{
	t_token	token;
	t_cmd	cmd1;
	t_cmd	cmd2;
}	t_pipe;
*/
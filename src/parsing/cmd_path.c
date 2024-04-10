//HEADER

#include "parsing.h"

int path_slash(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

void    search_path(char *cmd, t_env **env)
{
    (void)env;
    if (path_slash(cmd))
        return ;
}

void    cmd_path(t_input **input, t_env **env)
{
    t_input *node;

    node = *input;
    while (node)
    {
        if (node->tok == command)
            search_path(node->data[0], env);
        node = node->next;
    }
}
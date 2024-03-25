//HEADER

#include "minishell.h"
#include "parsing.h"

void    create_env(char **envp, t_env **env)
{
    int     i;
    t_env   *new;

    while (envp[i])
    {
        new = env_newnode(envp[i]);
        env_addback(env, new);
        i++;
    }
}

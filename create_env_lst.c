//HEADER

#include "minishell.h"
#include "parsing.h"

void    create_env(char **envp, t_env **env)
{
    int     i;
    t_env   *new;

    i = 0;
    new = NULL;
    while (envp[i])
    {
        new = env_newnode(envp[i]);
        if (!new)
            free_env(*env, EXIT_FAILURE, NULL);
        env_addback(env, new);
        i++;
    }
}

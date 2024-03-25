//HEADER

#include "minishell.h"
#include "parsing.h"

int main(int argc, char **argv, char **envp)
{
    t_env   *env;
    t_input *input;

    (void)argc;
    (void)argv;
    create_env(envp, &env);
    tokenization(&input, &env);
    return (0);
}

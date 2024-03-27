/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/27 09:51:59 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

void    export(t_env *env, char *var)
{
    char    **tab;
    t_env   *tmp;
    size_t  i;

    i = 0;
    tab = ft_split(var, '=');
    if (!tab)
        return (print_error(errno, "in export builtin"));
    tab[0] = ft_strjoin(tab[0], "=");
    if (!tab[0])
        return (print_error(errno, "in export builtin"));
    display_dtab(tab);
    tmp = env;
    while (tmp)
    {
        if (ft_strncmp(tab[0], tmp->env, ft_strlen(tab[0])) == 0)
        {
            printf("found match in node %ld : %s\n", i, tmp->env);
        }
        i++;
        tmp = tmp->next;
    }
    free_dtab(tab);
}
int main(int argc, char **argv, char  **envp)
{
    t_env   *env;

    env = NULL;
    if (argc == 2)
    {
        init_env(envp, &env);
        export(env, argv[1]);
        env_freelst(env);
        exit(EXIT_SUCCESS);
    }
    else
        print_error(0, "Expected one argument");
    exit(EXIT_FAILURE);
}
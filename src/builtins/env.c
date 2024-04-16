//HEADER

#include "exec.h"

int env(t_input *node)
{
    if (node->data[1])
    {
        if (ft_putstr_fd("too many arguments\n", 2) == -1)
            return (1);
        return (0); //????
    }
}
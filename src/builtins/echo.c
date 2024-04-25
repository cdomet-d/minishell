//HEADER

#include "exec.h"

int	cmp_opt(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-')
		return (1);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo(char **data)
{
	int		i;
	bool	opt;

	i = 1;
	opt = false;
	if (data && data[i])
	{
		if (!cmp_opt(data[i]))
		{
			i++;
			opt = true;
		}
		while (data[i])
		{
			if (ft_putstr_fd(data[i], STDOUT_FILENO) == -1)
				return (1);
			if (write(1, " ", 1) == -1)
				return (1);
			i++;
		}
	}
	if (opt == false)
		if (write(1, "\n", 1) == -1)
			return (1);
	return (0);
}

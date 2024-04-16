//HEADER

#include "exec.h"

int	echo(char **data, int fd)
{
	int		i;
	bool	opt;

	i = 0;
	opt = false;
	if (data)
	{
		if (!ft_strncmp(data[i], "-n", 3))
		{
			i++;
			opt = true;
		}
		while (data[i])
		{
			if (ft_putstr_fd(data[i], fd) == -1)
				return (1);
			i++;
		}
	}
	if (opt == false)
		if (write(1, "\n", fd) == -1)
			return (1);
	return (0);
}

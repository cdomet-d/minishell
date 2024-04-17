//HEADER

// #include "exec.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int	echo(char **data)
{
	int		i;
	bool	opt;

	i = 0;
	opt = false;
	if (data && data[0])
	{
		if (!/*ft_*/strncmp(data[i], "-n", 3))
		{
			i++;
			opt = true;
		}
		while (data[i])
		{
			// if (ft_putstr_fd(data[i], STDOUT_FILENO) == -1)
			// 	return (1);
			printf("%s", data[i]);
			printf("%c", ' ');
			i++;
		}
	}
	printf("\n");
	// if (opt == false)
		// if (write(1, "\n", 1) == -1)
			// return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	echo(argv + 1);
	return (0);
}
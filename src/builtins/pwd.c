//HEADER

#include "exec.h"

int	pwd(char **data)
{
	char	*str;

	str = NULL;
	if (data[1])
	{
		if (ft_putstr_fd("pwd : too many arguments\n", 2) == -1)
			return (1);
		return (0);
	}
	str = getcwd(NULL, 0);
	if (!str)
		return (1);
	if (ft_putstr_fd(str, 1) == -1)
		return (1);
	if (write(1, "\n", 1) == -1)
		return (1);
	free(str);
	return (0);
}

//HEADER

#include "parsing.h"

int	check_for_dollar(t_input *node)
{
	int	i;
	int	j;

	i = 0;
	if (!node->data)
		return (0);
	while (node->data[i])
	{
		j = 0;
		while (node->data[i][j])
		{
			if (node->data[i][j] == '$')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

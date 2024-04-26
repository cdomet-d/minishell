//HEADER

#include "exec.h"

int	search_dollar_hd(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	heredoc_expand(char **line, t_input *in)
{
	char	*temp;
	int		letter;

	letter = nb_letter(*line, &(in)->env);
	temp = ft_calloc(sizeof(char), letter + 1);
	if (!temp)
		return (1);
	ft_copy(*line, temp, &(in)->env, 0);
	free(*line);
	*line = temp;
	letter = 0;
	while (temp[letter])
	{
		if (temp[letter] < 0)
			*line[letter] = temp[letter] * -1;
		letter++;
	}
	return (0);
}

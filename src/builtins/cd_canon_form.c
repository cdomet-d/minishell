//HEADER

#include "exec.h"

char	*make_path(char *tab, char *path, char **temp)
{
	char	*tmp;

	free(*temp);
	*temp = NULL;
	if (path)
	{
		*temp = ft_strdup(path);
		if (!*temp)
			return (print_error(errno, NULL));
		tmp = ft_strjoin(path, tab);
	}
	else
		tmp = ft_strdup(tab);
	if (!tmp)
		return (free(path), print_error(errno, NULL));
	free(path);
	path = tmp;
	tmp = ft_strjoin(path, "/");
	free(path);
	if (!tmp)
		return (print_error(errno, NULL));
	path = tmp;
	return (path);
}

int	rm_dots(char **path, char **temp, char *tab, char *var)
{
	int		len;

	if (check_directory(var, *path))
		return (free(*temp), free(*path), 1);
	free(*path);
	*path = NULL;
	if (*temp)
	{
		*path = ft_strdup(*temp);
		if (!*path)
			return (free(*temp), 1);
		len = ft_strlen(tab) + 1;
		free(*temp);
		*temp = ft_substr(*path, 0, ft_strlen(*path) - len);
		if (!temp)
			return (free(*path), 1);
	}
	return (0);
}

char	*canonical_form(char *var, char *path, char **tab)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	j = 1;
	temp = NULL;
	while (tab[++i])
	{
		if (!ft_strncmp(tab[i], "..", 3) && (i - j) >= 0
			&& ft_strncmp(tab[i - j], ".", 2)
			&& ft_strncmp(tab[i - j], "..", 3))
		{
			if ((i - (j + 1)) >= 0)
				j++;
			if (rm_dots(&path, &temp, tab[i - j], var))
				return (NULL);
			j++;
		}
		else if (ft_strncmp(tab[i], ".", 2))
		{
			path = make_path(tab[i], path, &temp);
			if (!path)
				return (printf("shhh\n"), NULL);
		}
	}
	return (free(temp), path);
}

char	*prep_path(char *var, char *path)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	tab = ft_split(path, '/');
	if (!tab)
		return (free(path), NULL);
	if (path[0] == '/')
	{
		temp = ft_strdup("/");
		if (!temp)
			return (free_dtab(tab), print_error(errno, NULL));
	}
	free(path);
	path = NULL;
	path = canonical_form(var, temp, tab);
	free_dtab(tab);
	if (!path)
		return (NULL);
	return (path);
}

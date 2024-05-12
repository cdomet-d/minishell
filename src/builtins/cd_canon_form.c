//HEADER

#include "exec.h"

char	*make_path(char *tab, char *path, char **temp)
{
	char	*tmp;

	tmp = NULL;
	free(*temp);
	*temp = NULL;
	*temp = ft_strdup(path);
	if (!*temp)
		return (free(path), print_error(errno, NULL));
	tmp = ft_strjoin(path, tab);
	free(path);
	if (!tmp)
		return (free(*temp), print_error(errno, NULL));
	path = tmp;
	tmp = ft_strjoin(path, "/");
	free(path);
	if (!tmp)
		return (free(*temp), print_error(errno, NULL));
	path = tmp;
	return (path);
}

int	rm_dots(char **path, char **temp, char *tab, char *var)
{
	size_t	len;

	if (check_directory(var, *path))
		return (free(*temp), free(*path), 1);
	free(*path);
	*path = NULL;
	*path = ft_strdup(*temp);
	if (!*path)
		return (free(*temp), 1);
	len = ft_strlen(tab) + 1;
	free(*temp);
	*temp = ft_substr(*path, 0, ft_strlen(*path) - len);
	if (!*temp)
		return (free(*path), 1);
	return (0);
}

char	*canonical_form(char *var, char *path, char **tab, ssize_t j)
{
	ssize_t	i;
	char	*temp;

	i = -1;
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
				return (NULL);
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
	free(path);
	path = NULL;
	if (!tab)
		return (print_error(errno, NULL));
	temp = ft_strdup("/");
	if (!temp)
		return (free_dtab(tab), print_error(errno, NULL));
	path = canonical_form(var, temp, tab, 1);
	free_dtab(tab);
	if (!path)
		return (print_error(errno, NULL));
	return (path);
}

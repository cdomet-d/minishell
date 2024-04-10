//HEADER

#include "parsing.h"

int	path_len(char *env, int *i)
{
	int	len;

	len = 0;
	while (env[*i] && env[*i] != ':')
	{
		*i += 1;
		len++;
	}
	return (len);
}

char	*find_path(char *cmd, char *env)
{
	char	*path;
	int		letter;
	int		i;
	int		size;

	i = 0;
	path = NULL;
	while (env[i])
	{
		letter = path_len(env, &i);
		size = letter + (int)ft_strlen(cmd);
		path = ft_calloc(sizeof(char), size + 2);
		if (!path)
			return (NULL);
		fill_word(path, env + (i - letter), letter);
		path[letter++] = '/';
		fill_word(path + letter, cmd, (int)ft_strlen(cmd));
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		if (env[i])
			i++;
	}
	return (cmd);
}

int path_slash(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int    check_path(char *cmd, t_env **env)
{
	t_env	*node;
	char	*path;

	node = *env;
	path = NULL;
	if (path_slash(cmd))
		return (0);
	while (node)
	{
		if (!ft_strncmp(node->env, "PATH=", 5))
		{
			if (node->env[5])
			{
				path = find_path(cmd, node->env + 5);
				if (!path)
					return (1);
				printf("path : %s\n", path);
				cmd = path;
				free(path);
				return (0);
			}
		}
		node = node->next;
	}
	return (0);
}

int    cmd_path(t_input **input, t_env **env)
{
	t_input *node;

	node = *input;
	while (node)
	{
		if (node->tok == command)
		{
			if (check_path(node->data[0], env))
			{
				input_freelst(input);
				return (1);
			}
		}
		node = node->next;
	}
	return (0);
}
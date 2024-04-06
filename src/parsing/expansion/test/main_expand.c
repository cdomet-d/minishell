#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_input	*input;
	int     fd;

	(void)argv;
	line = NULL;
	env = NULL;
	input = NULL;
	if (argc != 1)
		fatal_exit(NULL, EXIT_FAILURE, "minishell: too many arguments");
	create_env(&input, envp, &env);
	fd = open("src/parsing/expansion/test/expand_test.txt", O_RDONLY);
	if (fd == -1)
	{
		dprintf(2, "shit\n");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	fd = open("src/parsing/expansion/test/result_expand.txt", O_RDWR, O_TRUNC);
	if (fd == -1)
	{
		printf("shiiiit\n");
		return (1);
	}
	while (1)
	{
		line = readline("Minishell > "); //besoin de proteger readline ???
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0 && line[0])
		{
			char    *buffer;
			int i = 0;
			// int j = 0;
			buffer = calloc(sizeof(char), 57);
			if (!buffer)
				mh_exit(line, input, env);
			i = read(fd, buffer, 5);
			if (i == -1 || !buffer[0])
			{
				close(fd);
				free(buffer);
				mh_exit(line, input, env);
			}
			printf("buffer : %s\n", buffer);
			// char   *result = "1\n1\n1\n1   \n1\n2\n1\n2   \n1\n2\n1\n2   \n2\n2\n2\n2   \n2\n2\n2\n2    \n1\n1\n2\n2";
			// i = 0;
			// while (buffer[i])
			// {
			// 	if (buffer[i] != result[i])
			// 		printf("test %d : wrong", j);
			// 	else
			// 		printf("test %d : right", j);
			// 	i += 2;
			// 	j++;
			// }
			close(fd);
			free(buffer);
			mh_exit(line, input, env);
		}
		parsing(&input, &env, line, fd);
		// exec_cmd(input);
		print_in_for(input);
		free(line);
		input_freelst(&input);
	}
	close(fd);
	return (0);
}
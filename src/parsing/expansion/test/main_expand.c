#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

void	print_words(char *buffer)
{
	int i;
	int	j = 1;

	char   *result = "1\n1\n1\n1\n1\n2\n1\n2\n1\n2\n1\n2\n1\n2\n1\n2\n2\n2\n2\n2\n2\n2\n2\n2\n1\n1\n2\n2\n2\n2\n2\n2\n2\n3\n2\n3\n3\n4\n3\n4\n3\n4\n3\n4\n4\n4\n4\n4\n4\n4\n4\n4\n2\n2\n3\n3\n0\n0\n1\n1\n1\n1\n0\n0\n2\n2\n2\n2\n2\n3\n3\n1\n1\n1\n1\n1\n1\n1\n2\n2\n2\n2\n2\n4\n3\n";
	i = 0;
	while (result[i])
	{
		if (result[i] == '\n')
		{
			if (buffer[i - 1] != result[i - 1])
				printf("test %d : wrong\n", j);
			else
				printf("test %d : right\n", j);
			j++;
		}
		i++;
	}
}

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
	// fd = open("src/parsing/expansion/test/result_expand.txt", O_RDWR, O_TRUNC);
	// if (fd == -1)
	// {
	// 	printf("shiiiit\n");
	// 	return (1);
	// }
	while (1)
	{
		line = readline("Minishell > "); //besoin de proteger readline ???
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0 && line[0])
		{
			// char    *buffer;
			// int i = 0;
			// int j = 1;
			// buffer = calloc(sizeof(char), 171);
			// if (!buffer)
			// 	mh_exit(line, input, env);
			// lseek(fd, 0, SEEK_SET);
			// i = read(fd, buffer, 170);
			// if (i == -1 || !buffer[0])
			// {
			// 	close(fd);
			// 	free(buffer);
			// 	mh_exit(line, input, env);
			// }
			// //printf_letter;
			// close(fd);
			// free(buffer);
			mh_exit(line, input, env);
		}
		parsing(&input, &env, line);
		// exec_cmd(input);
		print_in_for(input);
		free(line);
		input_freelst(&input);
	}
	return (0);
}
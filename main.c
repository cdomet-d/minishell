//HEADER

#include "minishell.h"
#include "parsing.h"

int main(int argc, char **argv, char **envp)
{
	t_env   *env;
	t_input *input;
	char    *line;

	(void)argc;
	(void)argv;
	line = NULL;
	env = NULL;
	input = NULL;
	create_env(envp, &env);
	while (1)
	{
		line = readline("Minishell > ");
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0) //si line == NULL ca s'arrete
			break ;
		tokenization(&input, &env, line);
	}
	while (input)
	{
		printf("input->tok: %d\n", input->tok);
		if (input->data)
			printf("input->data: %s\n", input->data[0]);
		input = input->next;
	}
	free_env(env, EXIT_SUCCESS, NULL);
	free_all(&input, EXIT_SUCCESS, NULL);
	return (0);
}

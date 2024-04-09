// #include "parsing.h"

// void	fill_env_quote(char *env, char *new, int *letter)
// {
// 	int	i;

// 	i = 0;
// 	if (!env)
// 		return ;
// 	while (env[i] && env[i] != '=')
// 		i++;
// 	i++;
// 	while (env[i])
// 	{
// 		new[*letter] = env[i]; 
// 		*letter += 1;
// 		i++;
// 	}
// }

// void	fill_env(char *env, char **newtab, int *word, int *letter)
// {
// 	int	i;

// 	i = 0;
// 	if (!env)
// 		return ;
// 	while (env[i] && env[i] != '=')
// 		i++;
// 	i++;
// 	while (env[i])
// 	{
// 		if (env[i] && (env[i] == ' ' || (env[i] >= '\t' && env[i] <= '\r')))
// 		{
// 			while (env[i] && (env[i] == ' ' || (env[i] >= '\t' && env[i] <= '\r')))
// 				i++;
// 			if (env[i])
// 			{
// 				*letter = 0;
// 				*word += 1;
// 			}
// 		}
// 		if (env[i])
// 		{
// 			newtab[*word][*letter] = env[i];
// 			i++;
// 			*letter += 1;
// 		}
// 	}
// }

// void	ft_fill(char **data, t_env **env, char **newtab)
// {
// 	int	i;
// 	int	j;
// 	int	word;
// 	int	letter;

// 	i = 0;
// 	word = 0;
// 	while (data[i])
// 	{
// 		letter = 0;
// 		j = 0;
// 		while (data[i][j])
// 		{
// 			if (data[i][j] == '\'')
// 			{
// 				newtab[word][letter++] = data[i][j++];
// 				while (data[i][j] && data[i][j] != '\'')
// 					newtab[word][letter++] = data[i][j++];
// 			}
// 			if (data[i][j] == '"')
// 			{
// 				newtab[word][letter++] = data[i][j++];
// 				while (data[i][j] && data[i][j] != '"')
// 				{
// 					if (data[i][j] == '$')
// 					{
// 						j++;
// 						fill_env_quote(search_env(data[i] + j, env), newtab[word], &letter);
// 						while (data[i][j] && data[i][j] != '$' && data[i][j] != '"'
// 							&& data[i][j] != '\'' && data[i][j] != ' '
// 							&& (data[i][j] < '\t' || data[i][j] > '\r'))
// 							j++;
// 					}
// 					else if (data[i][j])
// 						newtab[word][letter++] = data[i][j++];
// 				}
// 			}
// 			if (data[i][j] && data[i][j] == '$')
// 			{
// 				j++;
// 				fill_env(search_env(data[i] + j, env), newtab, &word, &letter);
// 				while (data[i][j] && data[i][j] != '$' && data[i][j] != '"'
// 					&& data[i][j] != '\'')
// 					j++;
// 			}
// 			else if (data[i][j])
// 				newtab[word][letter++] = data[i][j++];
// 		}
// 		i++;
// 		word++;
// 	}
// }
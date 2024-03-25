//HEADER

#ifndef PARSING_H
# define PARSING_H

void    create_env(char **envp, t_env **env);
void    tokenization(t_input **input, t_env **env, char *line);

#endif
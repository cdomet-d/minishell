//HEADER

#include "parsing.h"

// typedef struct s_expand
// {
//     int     i;
//     int     j;
//     int     null;
//     char    *str;
//     char    *tmp;
//     char    **save;
//     bool    dollar;
// } t_exp;

// bool	nb_word_env(char *str, int *word, char c)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] != ' ' && (str[i] < '\t' || str[i] > '\r'))
// 			&& (str[i + 1] == ' ' || (str[i + 1] >= '\t'
// 					&& str[i + 1] <= '\r')))
// 			*word += 1;
// 		i++;
// 	}
// 	if ((str[i - 1] == ' ' || (str[i - 1] >= '\t' && str[i - 1] <= '\r'))
// 		&& c == '\0')
//         return (true);
//     return (false);
// }

// void	in_quotes(char *data, t_exp *var)
// {
// 	char	quotetype;

// 	quotetype = data[var->j];
// 	var->j += 1;
// 	while (data[var->j] && data[var->j] != quotetype)
// 		var->j += 1;
// }

// void	check_var_env(char *data, t_env **env, t_exp *var)
// {
// 	int	len;

// 	while (!var->str && data[var->j] && data[var->j] == '$')
// 	{
// 		var->str = search_env(data + (var->j + 1), env);
// 		if (!var->str)
// 		{
// 			var->j += 1;
// 			var->null += 1;
// 			while (data[var->j] && data[var->j] != '$' && data[var->j] != '"'
// 				&& data[var->j] != '\'')
// 			{
// 				var->null += 1;
// 				var->j += 1;
// 			}
// 		}
// 	}
// 	if (var->null == (int)ft_strlen(data))
// 		var->dollar = true;
// 	var->null++;
// 	len = (int)ft_strlen(var->tmp) - 1;
// 	if (!var->str && data[var->j] == '\0' && (var->j - var->null) > 0
// 		&& data[var->j - var->null] < 0 && var->tmp && (var->tmp[len] == ' '
// 		|| (var->tmp[len] >= '\t' && var->tmp[len] <= '\r')))
// 		var->dollar = true;
// }

// void	var_env(char *data, int *word, t_exp *var)
// {
// 	int	len;

// 	len = 0;
// 	if (var->j != 0 && (var->j - var->null) > 0 && data[var->j - var->null] < 0)
// 	{
// 		len = (int)ft_strlen(var->tmp) - 1;
// 		if (var->tmp && var->tmp[len] != ' ' && (var->tmp[len] < '\t' || var->tmp[len] > '\r')
// 			&& (var->str && (var->str[0] == ' ' || (var->str[0] >= '\t' && var->str[0] <= '\r'))))
// 		{
// 			*word += 1;
// 			// var->save[var->i][var->j] *= -1;
// 		}
// 	}
// 	if (var->j != 0 && (var->j - var->null) > 0 && data[var->j - var->null] > 0
// 		&& ((var->str && (var->str[0] == ' ' || (var->str[0] >= '\t' && var->str[0] <= '\r')))))
// 		*word += 1;
// 	var->j += 1;
// 	while (data[var->j] && data[var->j] != '$' && data[var->j] != '"'
// 		&& data[var->j] != '\'')
// 	{
// 		data[var->j] *= -1;
// 		var->j += 1;
// 	}
// }

// void	in_dollar(char *data, t_env **env, int *word, t_exp *var)
// {
// 	var->null = 0;
// 	check_var_env(data, env, var);
// 	if (var->str)
// 	{
// 		var_env(data, word, var);
// 		var->dollar = nb_word_env(var->str, word, data[var->j]);
// 		var->tmp = var->str;
// 		var->str = NULL;
// 	}
// }

// void	nb_word(char **data, char **save, t_env **env, int *word)
// {
// 	t_exp	var;

// 	var.i = 0;
// 	var.null = 0;
// 	var.str = NULL;
// 	var.tmp = NULL;
// 	var.save = save;
// 	while (data[var.i])
// 	{
// 		var.dollar = false;
// 		var.j = 0;
// 		while (data[var.i][var.j])
// 		{
// 			if (data[var.i][var.j] == '"' || data[var.i][var.j] == '\'')
// 				in_quotes(data[var.i], &var);
// 			if (data[var.i][var.j] == '$')
// 				in_dollar(data[var.i], env, word, &var);
// 			else if (data[var.i][var.j])
// 				var.j++;
// 		}
// 		if (var.dollar == false)
//             *word += 1;
// 		var.i++;
// 	}
// 	free_dtab(data);
// 	// revert(data);
// }

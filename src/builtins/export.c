/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:23:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/26 13:40:42 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	is_sorted(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], tab[i + 1], 1) > 0)
			return (false);
		i++;
	}
	return (true);
}

void *sort_env(t_env	*env)
{
	char	**arenv;
	char	*tenv;
	size_t	i;
	size_t	j;
	size_t	len;
	
	i = 0;
	len = 0;
	arenv = arenvlst(env);
	if (!arenv)
		return (print_error(errno, "minishell"));
	while (arenv[len])
		len++;
	vdisplay_dtab(arenv);
	printf("\n");
	while (!is_sorted(arenv))
	{
		j = i + 1;
		if (ft_strncmp(arenv[i], arenv[j], 1) > 0)
		{
			tenv = arenv[i];
			arenv[i] = arenv[j];
			arenv[j] = tenv;
		}
		if (i < len)
			i++;
		elseg
			i = 0;
	}
	vdisplay_dtab(arenv);
	free_dtab(arenv);
	return ((int *)true);
}

static void	*exprt_inenv(t_env **env, char *data)
{
	t_env	*new;

	new = env_newnode(data);
	if (!new)
		return (NULL);
	env_addback(env, new);
	return (new);
}

void	*export(t_input **in, char *var)
{
	char	*key;
	t_env	*head;
	
	fprintf(stderr, "%.20s\n", "-- export ---------------------------------");
	if (!(*in)->env)
		return (print_error(errno, "NULL param in export"));
	if (!var)
		sort_env((*in)->env);
	key = split_wsep(var, '=');
	if (!key)
		return (print_error(errno, NULL));
	head = (*in)->env;
	while ((*in)->env)
	{
		if (ft_strncmp(key, (*in)->env->env, ft_strlen(key)) == 0)
		{
			free((*in)->env->env);
			free(key);
			(*in)->env->env = ft_strdup(var);
			(*in)->env = head;
			return ((*env));
		}
		(*in)->env = (*in)->env->next;
	}
	free(key);
	(*in)->env = head;
	exprt_inenv(&(*in)->env, var);
	return (in);
}

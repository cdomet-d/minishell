/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:03:33 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/08 16:00:49 by jauseff          ###   ########lyon.fr   */
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

static char	**sort_tab(char **arenv, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tenv;

	i = 0;
	while (arenv[i])
	{
		j = i + 1;
		if (j <= len && ft_strncmp(arenv[i], arenv[j], ft_strlen(arenv[i])) > 0)
		{
			tenv = arenv[i];
			arenv[i] = arenv[j];
			arenv[j] = tenv;
		}
		i++;
	}
	return (arenv);
}

static ssize_t	print_senv(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (printf("> %s\n", arr[i]) == -1)
			return (1);
		i++;
	}
	return (1);
}

int	sort_env(t_env	*env)
{
	char	**arenv;
	size_t	len;
	ssize_t	rv;

	arenv = arenvlst(env);
	if (!arenv)
		return (parsing_error("minishell: ", "export: ", strerror(errno)));
	len = ft_arrlen(arenv);
	while (!is_sorted(arenv))
		arenv = sort_tab(arenv, len);
	rv = print_senv(arenv);
	free_dtab(arenv);
	if (rv == -1)
		return (1);
	return (0);
}

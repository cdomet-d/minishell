/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:03:33 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/04/26 15:34:28 by cdomet-d         ###   ########lyon.fr   */
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

static void	print_senv(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		printf("declare -x ");
		printf("%c%s%c\n", 34, arr[i], 34);
		i++;
	}
}

void	*sort_env(t_env	*env)
{
	char	**arenv;
	size_t	len;

	arenv = arenvlst(env);
	if (!arenv)
		return (print_error(errno, "minishell"));
	len = ft_arrlen(arenv);
	while (!is_sorted(arenv))
		arenv = sort_tab(arenv, len);
	print_senv(arenv);
	free_dtab(arenv);
	return ((int *)true);
}

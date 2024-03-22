/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:47:07 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/22 13:47:10 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	lst_free(t_input **lst)
{
	t_input	*ptr;
	t_input	*temp;

	if (!lst || !*lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		temp = ptr->next;
		free(ptr);
		ptr = temp;
	}
	lst = NULL;
}

void	add_back(t_input **lst, t_input *node)
{
	if (!lst || !node)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = node;
		node->prev = *lst;
	}
}

t_input	*create_node(char **data, t_tok token, t_env **env)
{
	t_input	*new;

	new = malloc(sizeof(t_input) * 1);
	if (!new)
		return (NULL);
	new->data = data;
	new->tok = token;
	new->env = env;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

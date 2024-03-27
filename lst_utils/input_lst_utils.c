/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:47:07 by csweetin          #+#    #+#             */
/*   Updated: 2024/03/27 16:07:28 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input_freelst(t_input **lst)
{
	t_input	*temp;

	temp = NULL;
	if (!lst || !*lst)
		return ;
	// if ((*lst)->env)
	// 	env_freelst((*lst)->env);
	while (*lst)
	{
		temp = (*lst)->next;
		free_dtab((*lst)->data);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	input_addback(t_input **lst, t_input *node)
{
	t_input	*head;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		head = (*lst);
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		(*lst)->next = node;
		node->prev = (*lst);
		(*lst) = head;
	}
}

t_input	*input_newnode(char **data, int token, t_env *env)
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

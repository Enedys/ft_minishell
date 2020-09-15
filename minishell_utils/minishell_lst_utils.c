/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lst_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walline <walline@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:40:44 by walline           #+#    #+#             */
/*   Updated: 2020/08/02 00:55:16 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

void		ft_dellst(t_list **lst)
{
	t_list	*cur;
	t_list	*t;

	cur = *lst;
	if (!cur)
		return ;
	while (cur)
	{
		t = cur;
		free(cur->data);
		cur->data = NULL;
		cur = cur->next;
		t->prev = NULL;
		t->next = NULL;
		free(t);
		t = NULL;
	}
	*lst = NULL;
}

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cur;

	cur = *alst;
	if (cur)
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		new->prev = cur;
	}
	else
		*alst = new;
}

t_list		*ft_lstnew(void *content)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->data = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		ft_envlstadd_back(t_env **alst, t_env *new)
{
	t_env	*cur;

	cur = *alst;
	if (cur)
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	else
		*alst = new;
}

t_env		*ft_envlstnew(char *name, char *value, int visible)
{
	t_env	*new;

	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->name = name;
	new->value = value;
	new->visible = visible;
	new->next = NULL;
	return (new);
}

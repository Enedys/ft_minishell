/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walline <walline@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 09:57:28 by walline           #+#    #+#             */
/*   Updated: 2020/07/30 09:57:29 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_replacevar(t_data *data)
{
	t_list	*temp;
	char	*str;

	temp = data->args;
	while (temp)
	{
		str = temp->data;
		if (ft_strchr(str, -1))
		{
			temp->data = ft_getresultstr(data, str);
			ft_delstr(str);
		}
		temp = temp->next;
	}
}

void		ft_delsep(t_data *data)
{
	t_list	*temp;

	temp = data->args;
	while (temp)
	{
		if (temp->type == SEP && temp->prev->type == VAR)
			if (!ft_dellstnode(data, &temp))
			{
				temp = data->args;
				continue;
			}
		temp = temp->next;
	}
}

t_list		*ft_lstdup(t_list *lst)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->data = ft_strdup(lst->data);
	new->type = lst->type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int			ft_getcmd(t_data *data)
{
	ft_dellst(&data->args);
	while (data->tokens && data->tokens->type != SEP)
	{
		ft_lstadd_back(&data->args, ft_lstdup(data->tokens));
		data->tokens = data->tokens->next;
	}
	if (data->tokens && data->tokens->next)
		data->tokens = data->tokens->next;
	if (data->args == NULL)
		return (0);
	return (1);
}

int			ft_iscmdvalid(t_list *l)
{
	while (l)
	{
		if ((l->type == PIPE || ft_isctoken(l->type)) && l->prev == NULL)
			return (0);
		if ((l->type == PIPE && l->next && ft_isctoken(l->next->type)))
			return (0);
		l = l->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walline <walline@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:47:59 by walline           #+#    #+#             */
/*   Updated: 2020/08/13 21:18:28 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int				ft_countenv(t_env *lst)
{
	int			c;

	c = 0;
	while (lst)
	{
		if (lst->visible)
			c++;
		lst = lst->next;
	}
	return (c);
}

void			ft_delenv(t_env **lst)
{
	t_env		*cur;
	t_env		*t;

	cur = *lst;
	while (cur)
	{
		t = cur;
		free(cur->name);
		free(cur->value);
		cur->name = NULL;
		cur->value = NULL;
		cur = cur->next;
		t->next = NULL;
		free(t);
		t = NULL;
	}
	*lst = NULL;
}

char			**ft_getenvarr(t_env *lst)
{
	int			i;
	char		**ret;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (ft_countenv(lst) + 1));
	while (lst)
	{
		if (lst->visible >= 2)
			ret[i++] = ft_strappend(ft_strappend(ft_strdup(lst->name), \
			ft_strdup("=")), ft_strdup(lst->value));
		lst = lst->next;
	}
	ret[i] = NULL;
	return (ret);
}

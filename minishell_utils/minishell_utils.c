/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:21:03 by walline           #+#    #+#             */
/*   Updated: 2020/08/14 19:35:06 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int			ft_isctoken(int i)
{
	if (i == SEP || i == WRITE || i == READ || i == APPEND)
		return (1);
	return (0);
}

int			ft_istokensvalid(t_list *l)
{
	while (l)
	{
		if (ft_isctoken(l->type) && (!l->next || ft_isctoken(l->next->type)) \
			&& (!l->prev || ft_isctoken(l->prev->type)))
		{
			write(1, "-minishell: syntax error\n", 25);
			return (0);
		}
		if (((l->type == WRITE || l->type == READ || l->type == APPEND) \
			&& !l->next) || (ft_isctoken(l->type) && !l->prev))
		{
			write(1, "-minishell: syntax error\n", 25);
			return (0);
		}
		if ((ft_isctoken(l->type) && (l->prev && ft_isctoken(l->prev->type)))\
		|| (l->type == PIPE && (l->prev && l->prev->type == PIPE)))
		{
			write(1, "-minishell: syntax error\n", 25);
			return (0);
		}
		l = l->next;
	}
	return (1);
}

int			ft_varcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 != ':' && *s2 != ' ' && *s2 > 0)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 == '\0' && (*s2 == '\0' || *s2 == ':'))
		return (1);
	return (0);
}

char		*ft_getvarvalue(t_data *data, char *str, int *i)
{
	t_env	*temp;
	char	*s;
	char	*var;
	char	*free;

	temp = data->env;
	while (temp)
	{
		s = temp->name;
		var = ft_substr(str, 0, ft_strchr(str, -1) - str);
		free = var;
		if (ft_varcmp(s, var))
		{
			while (*s && *var && *var++ == *s++)
				(*i)++;
			ft_delstr(free);
			return (temp->value);
		}
		ft_delstr(free);
		temp = temp->next;
	}
	return (NULL);
}

char		*ft_getresultstr(t_data *data, char *str)
{
	int		i;
	char	*temp;
	char	*ret;
	char	*value;

	temp = (char *)malloc(BUF);
	ret = temp;
	i = 0;
	while (str[i])
	{
		while (str[i] > 0)
			*temp++ = str[i++];
		i++;
		if ((value = ft_getvarvalue(data, &str[i], &i)))
			while (*value)
				*temp++ = *value++;
		else
			while (str[i] > 0 && str[i] != ' ')
				i++;
		while (str[i] > 0)
			*temp++ = str[i++];
	}
	*temp = '\0';
	return (ret);
}

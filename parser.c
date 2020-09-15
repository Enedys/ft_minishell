/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 14:46:54 by walline           #+#    #+#             */
/*   Updated: 2020/08/14 00:20:24 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_deleteescapes(char **str, char *temp, int i, char *s)
{
	while (s[i])
	{
		if (s[0] == '\\' && s[1] == '\0')
		{
			temp = ft_strdup(" ");
			break ;
		}
		if (s[i] == '\\' && !ft_recquot(s, i))
			i++;
		else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\') && \
			ft_recquot(s, i) == 2)
			i++;
		while ((s[i] == '\'' || s[i] == '\"') && !ft_isslashquot(s, i) && \
			ft_takequot(s, i) && !((ft_recquot(s, i) == 1 && s[i] == '\"') || \
			(ft_recquot(s, i) == 2 && s[i] == '\'')))
			i++;
		if (s[i] == '\\' && s[i + 1] == '\"')
			i++;
		temp = ft_strappend(temp, ft_substr(s, i, 1));
		i++;
	}
	free(*str);
	*str = temp;
}

char		*ft_processline(char *str, int i, int j)
{
	char	*ret;

	ret = (char *)malloc(BUF);
	while (str[i])
	{
		if (str[i] == '$' && ft_recquot(str, i) != 1)
		{
			ret[j++] = (char)(-1);
			i++;
		}
		else if (!ft_recquot(str, i) && ft_istoken(str, i))
		{
			ret[j++] = ' ';
			ret[j++] = str[i++];
			if (str[i] == '>' && !ft_recquot(str, i))
				ret[j++] = str[i++];
			ret[j++] = ' ';
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	ft_delstr(str);
	return (ret);
}

char		*ft_getnextarg(char *s, int *i, int q)
{
	char	*temp;
	char	*begin;

	temp = (char *)ft_calloc(BUF, 1);
	begin = temp;
	while (s[*i] && (s[*i] != ' ' || (s[*i] == ' ' && *i - 1 > 0 && s[*i - 1] \
	== '\\' && ft_countslashbackward(s, *i - 1)) || q))
	{
		if ((q == 1 && s[*i] == '\'' && *i > 0 && s[*i - 1] != '\\') || \
			(q == 2 && s[*i] == '\"' && *i > 0 && s[*i - 1] != '\\'))
		{
			*(temp++) = s[(*i)++];
			q = 0;
			continue;
		}
		if (!q && s[*i] == '\'' && ((*i > 0 && s[*i - 1] != '\\') || *i == 0))
			q = 1;
		else if (!q && s[*i] == '\"' && ((*i > 0 && s[*i - 1] != '\\') || \
				*i == 0))
			q = 2;
		*(temp++) = s[(*i)++];
	}
	*temp = '\0';
	return (begin);
}

t_list		*ft_getargslst(char *str)
{
	t_list	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		ft_lstadd_back(&ret, ft_lstnew(ft_getnextarg(str, &i, 0)));
		if (str[i])
			i++;
	}
	return (ret);
}

void		ft_parseline(t_data *data)
{
	t_list	*t;

	data->line = ft_processline(data->line, 0, 0);
	if (data->line)
		data->args = ft_getargslst(data->line);
	ft_recargtypes(data->args, 0, 0);
	t = data->args;
	while (t)
	{
		ft_deleteescapes(&t->data, ft_strdup(""), 0, t->data);
		t = t->next;
	}
}

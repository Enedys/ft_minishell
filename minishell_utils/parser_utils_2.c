/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 12:39:03 by walline           #+#    #+#             */
/*   Updated: 2020/08/13 21:13:05 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

static int	ft_xz(char *eq, char *str)
{
	char	*q;
	char	*dq;

	q = ft_strchr(str, '\'');
	dq = ft_strchr(str, '\"');
	if (((eq && (!q && !dq) && !ft_recquot(str, eq - str)) || \
				(eq && ((q && eq < q) || (dq && eq < dq)) && \
				!ft_recquot(str, eq - str))))
		return (1);
	return (0);
}

void		ft_vartype(t_list *temp, char *eq, char *str, int f)
{
	if (!f && ((temp->prev && (temp->prev->type != CMD || \
			temp->prev->type != SEP)) || !temp->prev) && ft_xz(eq, str))
		temp->type = VAR;
}

void		ft_recargtypes(t_list *temp, int f, char *str)
{
	while (temp)
	{
		str = temp->data;
		if (*str == '|')
			temp->type = PIPE;
		else if (ft_strcmp(str, ">>", 1))
			temp->type = APPEND;
		else if (*str == '>')
			temp->type = WRITE;
		else if (*str == '<')
			temp->type = READ;
		else if (*str == ';' && !(f = 0))
			temp->type = SEP;
		else if ((!temp->prev || (temp->prev && (temp->prev->type == 2 || temp->
		prev->type == 1 || temp->prev->type == 8))) && !ft_strchr(str, '='))
		{
			if (!ft_xz(ft_strchr(str, '='), str))
				f = 1;
			temp->type = CMD;
		}
		else
			temp->type = ARG;
		ft_vartype(temp, ft_strchr(str, '='), str, f);
		temp = temp->next;
	}
}

int			ft_takequot(char *str, int i)
{
	int		c;
	int		q;

	c = 0;
	q = 0;
	while (str[c] && c <= i)
	{
		if (c > 0 && str[c - 1] == '\\' && str[c] != '\'')
			;
		else if (q == 0 && str[c] == '\'' && \
				((c > 0 && str[c - 1] != '\\') || !c))
			q = 1;
		else if (q == 0 && str[c] == '\"' && \
				((c > 0 && str[c - 1] != '\\') || !c))
			q = 2;
		c++;
	}
	return (q);
}

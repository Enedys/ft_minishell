/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walline <walline@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:38:55 by walline           #+#    #+#             */
/*   Updated: 2020/08/13 21:17:39 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

char			*ft_getchraddrend(char *str, int c)
{
	int			len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == c)
			return (&str[len]);
		len--;
	}
	return (str);
}

int				ft_strcmp(const char *s1, const char *s2, int prec)
{
	while (*s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 != '\0' && prec == 1)
		return (0);
	if (*s1 != '\0' && prec == 2)
		return (1);
	return (1);
}

char			*ft_getchraddr(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	return (str);
}

int				ft_getaddline(t_data *data, int slash, int *err, char *t)
{
	char		*te;

	if (slash == 2 && (ft_countwords(data->line) < 2) && (*err = 1))
		return (1);
	if (slash)
		te = data->line;
	else
		te = ft_strappend(data->line, ft_strdup("\n"));
	if (*err != 1)
		write(1, "> ", 2);
	if (get_next_line(1, &data->line, 1) == -1)
	{
		ft_delstr(te);
		return (-1);
	}
	if (slash == 1)
	{
		t = te;
		te = ft_strappend(ft_substr(te, 0, ft_strlen(te) - 1), ft_strdup(""));
		ft_delstr(t);
	}
	if (slash == 2 && (*(data->line) == '|'))
		*err = 1;
	data->line = ft_strappend(te, data->line);
	return (0);
}

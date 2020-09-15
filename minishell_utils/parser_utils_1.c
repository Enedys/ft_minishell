/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walline <walline@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 09:57:28 by walline           #+#    #+#             */
/*   Updated: 2020/07/30 09:57:29 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_recquot(char *str, int i)
{
	int		c;
	int		q;

	c = 0;
	q = 0;
	while (str[c] && c < i)
	{
		if (c > 0 && str[c - 1] == '\\' && str[c] != '\'')
			;
		else if (q == 0 && str[c] == '\'' && \
				((c > 0 && str[c - 1] != '\\') || !c))
			q = 1;
		else if (q == 0 && str[c] == '\"' && \
				((c > 0 && str[c - 1] != '\\') || !c))
			q = 2;
		else if ((q == 1 && str[c] == '\'') || (q == 2 && str[c] == '\"'))
			q = 0;
		c++;
	}
	return (q);
}

int			ft_isopenslash(char *str)
{
	int		c;

	c = 0;
	while (*str)
	{
		if (!c && *str == '\\')
		{
			c = 1;
			str++;
			continue;
		}
		if (c)
		{
			c = 0;
			str++;
			continue;
		}
		str++;
	}
	return (!c);
}

int			ft_isslashquot(char *s, int i)
{
	int		c;
	int		os;
	int		j;

	c = 0;
	j = -1;
	os = 0;
	while (s[++j] && j <= i)
	{
		if ((s[j] == '\'' || s[j] == '\"') && j > 0 && s[j - 1] == '\\' && os)
			c = 1;
		else
			c = 0;
		if (!os && s[j] == '\\')
		{
			os = 1;
			continue;
		}
		if (os)
		{
			os = 0;
			continue;
		}
	}
	return (c);
}

int			ft_isvalidquot(char *s)
{
	int		i;
	int		q;

	i = 0;
	q = 0;
	while (s[i])
	{
		if (((q == 1 && s[i] == '\'') || (q == 2 && s[i] == '\"' && \
			!ft_isslashquot(s, i))))
		{
			i++;
			q = 0;
			continue;
		}
		if (!q && s[i] == '\'' && !ft_isslashquot(s, i))
			q = 1;
		else if (!q && s[i] == '\"' && !ft_isslashquot(s, i))
			q = 2;
		i++;
	}
	if (q)
		return (0);
	return (1);
}

int			ft_istoken(char *line, int i)
{
	int		tok;

	tok = 0;
	if (line[i] == '<' || line[i] == '>' || line[i] == '|' || line[i] == ';')
		tok = 1;
	if ((i > 0 && line[i - 1] == '\\' && tok))
		return (0);
	else if (!ft_recquot(line, i) && tok)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walline <walline@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:38:17 by walline           #+#    #+#             */
/*   Updated: 2020/08/13 20:44:01 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int				ft_countwords(char *str)
{
	int			c;

	c = 0;
	if (!str)
		return (0);
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		if (*str && *str != ' ')
		{
			while (*str && *str != ' ')
				str++;
			c++;
		}
	}
	return (c);
}

void			ft_delstr(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void			ft_delarr(char **arr)
{
	int			i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}

int				ft_countarrlen(char **arr)
{
	int			i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

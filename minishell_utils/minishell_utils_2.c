/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 12:24:21 by walline           #+#    #+#             */
/*   Updated: 2020/08/13 21:15:09 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

static void		ft_sortenvarr(char **arr)
{
	int			sorted;
	int			i;
	char		*temp;
	int			len;

	sorted = 0;
	len = ft_countarrlen(arr);
	while (arr && !sorted)
	{
		sorted = 1;
		i = 0;
		while (i < len - 1)
		{
			if (ft_strncmp(arr[i], arr[i + 1], -1) > 0)
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
		len--;
	}
}

void			ft_printsortedenv(char **arr, int i, int j)
{
	ft_sortenvarr(arr);
	while (arr[i])
	{
		j = 0;
		write(1, "declare -x ", 11);
		if ((ft_strchr(arr[i], '=')))
		{
			while (arr[i][j] != '=')
			{
				write(1, &arr[i][j], 1);
				j++;
			}
			j++;
			write(1, "=\"", 2);
			ft_putstr_fd(&arr[i][j], 1);
			write(1, "\"", 1);
		}
		else
		{
			ft_putstr_fd(&arr[i][j], 1);
			write(1, "=\"\"", 3);
		}
		write(1, "\n", 1);
		i++;
	}
}

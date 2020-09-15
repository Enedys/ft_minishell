/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walline <walline@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 09:57:28 by walline           #+#    #+#             */
/*   Updated: 2020/07/30 09:57:29 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

int			ft_arrnum(int *arr, int num, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (arr[i] == num)
			return (1);
		i++;
	}
	return (0);
}

int			*ft_get_invalid_arg_index_arr(char **data)
{
	int		j;
	int		i;
	int		*index;

	index = (int *)malloc(sizeof(int) * 64);
	j = 0;
	while (j < 64)
		index[j++] = -1;
	j = 0;
	i = 1;
	while (data[i])
	{
		if (!ft_checkvar(data[i], 1))
		{
			index[j] = i;
			j++;
		}
		i++;
	}
	return (index);
}

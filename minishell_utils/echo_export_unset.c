/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_export_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 23:52:38 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 20:46:11 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"
#include "../kwillum_part/includes.h"

int			ft_export(t_data *data)
{
	int		i;
	int		ret;
	int		var;
	int		*index;

	i = 0;
	index = ft_get_invalid_arg_index_arr(data->params);
	if (index[0] != -1)
		ret = 1;
	ft_delarr(data->env_arr);
	i = 1;
	while (data->params[i])
	{
		if (!ft_arrnum(index, i, 64))
			env_support(data, i);
		i++;
	}
	data->env_arr = ft_getenvarr(data->env);
	if (i == 1)
		ft_printsortedenv(data->env_arr, 0, 0);
	free(index);
	return (stop_process(data, ret));
}

char		**ft_arrdelstr(char **arr, int index)
{
	int		i;
	int		len;
	char	**ret;
	int		j;

	i = 0;
	j = 0;
	len = ft_countarrlen(arr);
	ret = (char **)malloc(sizeof(char *) * len);
	while (arr[i])
	{
		i == index ? i++ : 0;
		if (!arr[i])
			break ;
		ret[j++] = arr[i++];
	}
	ret[j] = NULL;
	ft_delstr(arr[index]);
	free(arr);
	return (ret);
}

int			ft_unset(t_data *data)
{
	int		i;
	int		var;

	i = 1;
	ft_delarr(data->env_arr);
	data->env_arr = ft_getenvarr(data->env);
	while (data->params[i])
	{
		if ((var = ft_findvararr(data->params[i], data->env_arr, 0, 0)) >= 0)
			data->env_arr = ft_arrdelstr(data->env_arr, var);
		change_env_var(get_env_var(data->env, data->params[i]), "", 0);
		i++;
	}
	return (stop_process(data, 0));
}

int			ft_echo(t_data *data)
{
	int		i;

	i = 1;
	if (data->params[i] && ft_strcmp(data->params[i], "-n", 1))
		i++;
	while (data->params[i])
	{
		write(1, data->params[i], ft_strlen(data->params[i]));
		if (data->params[i + 1])
			write(1, " ", 1);
		i++;
	}
	if ((i > 1 && !ft_strcmp(data->params[1], "-n", 1)) || i == 1)
		write(1, "\n", 1);
	return (stop_process(data, 0));
}

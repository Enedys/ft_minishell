/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:29:34 by walline           #+#    #+#             */
/*   Updated: 2020/08/14 21:36:14 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"
#include "../kwillum_part/includes.h"

int			ft_findvararr(char *str, char **arr, int i, int j)
{
	char	*name;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (eq)
		name = ft_substr(str, 0, eq - str);
	else
		name = str;
	while (arr[i])
	{
		j = 0;
		while (name[j] && arr[i][j] && (name[j] == arr[i][j]))
			j++;
		if (name[j] == '\0' && (arr[i][j] == '=' || arr[i][j] == '\0'))
		{
			if (eq)
				ft_delstr(name);
			return (i);
		}
		i++;
	}
	if (eq)
		ft_delstr(name);
	return (-1);
}

char		**ft_arraddback(char **arr, char *str)
{
	int		i;
	int		len;
	char	**ret;

	i = 0;
	len = ft_countarrlen(arr);
	ret = (char **)malloc(sizeof(char *) * (len + 2));
	while (arr[i])
	{
		ret[i] = arr[i];
		i++;
	}
	ret[i] = ft_strdup(str);
	ret[++i] = NULL;
	free(arr);
	return (ret);
}

void		env_support(t_data *data, int i)
{
	char	*tmp;
	t_env	*prev;

	if ((tmp = ft_strchr(data->params[i], '=')))
		*tmp = '\0';
	if (!(prev = get_env_var(data->env, data->params[i])))
		create_env_var(data->env, data->params[i], tmp ? tmp + 1 \
		: "", tmp ? 3 : 2);
	else
		change_env_var(prev, tmp ? tmp + 1 : NULL, tmp ? 3 : prev->visible | 2);
	if (tmp)
		*tmp = '=';
}

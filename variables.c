/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 09:55:59 by walline           #+#    #+#             */
/*   Updated: 2020/08/14 00:20:24 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*ft_createenv(char *str, int visible)
{
	char	*name;
	char	*value;
	char	*eq;

	if ((eq = ft_strchr(str, '=')))
	{
		name = ft_substr(str, 0, eq - str);
		value = ft_strdup(eq + 1);
	}
	else
	{
		name = ft_strdup(str);
		value = ft_strdup("");
	}
	return (ft_envlstnew(name, value, visible));
}

void		ft_createenvlst(t_data *data, char **env)
{
	int		i;

	i = 0;
	data->env = NULL;
	while (env[i])
		ft_envlstadd_back(&data->env, ft_createenv(env[i++], 3));
	set_pwd_env(data->env);
}

t_env		*ft_findvar(char *str, t_env *var)
{
	char	*name;
	char	*eq;
	t_env	*temp;

	eq = ft_strchr(str, '=');
	name = ft_substr(str, 0, eq - str);
	temp = var;
	while (temp)
	{
		if (ft_strcmp(name, temp->name, 1))
		{
			ft_delstr(name);
			return (temp);
		}
		temp = temp->next;
	}
	ft_delstr(name);
	return (NULL);
}

void		ft_processvar(t_data *data, t_list *temp, char *eq, int i)
{
	t_env	*var;

	while (data->env_arr[i])
	{
		if (ft_varcmp(data->env_arr[i], temp->data))
		{
			free(data->env_arr[i]);
			data->env_arr[i] = ft_strdup(temp->data);
		}
		i++;
	}
	if (!(var = ft_findvar(temp->data, data->env)))
		ft_envlstadd_back(&data->env, ft_createenv(temp->data, 1));
	else
	{
		ft_delstr(var->value);
		var->value = ft_strdup(eq + 1);
		var->visible = var->visible | 1;
	}
}

int			ft_getvariables(t_data *data, t_list *temp, char *s)
{
	temp = data->args;
	while (temp)
	{
		if (temp->type == VAR)
		{
			if (!ft_checkvar(temp->data, 0))
				return (0);
			if (ft_strchr(temp->data, -1))
			{
				s = temp->data;
				temp->data = ft_getresultstr(data, temp->data);
				ft_delstr(s);
			}
			ft_processvar(data, temp, ft_strchr(temp->data, '='), 0);
			ft_delsep(data);
			if (!ft_dellstnode(data, &temp))
			{
				temp = data->args;
				continue;
			}
		}
		temp = temp->next;
	}
	return (1);
}

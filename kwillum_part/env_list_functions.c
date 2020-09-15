/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 22:15:04 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/13 17:59:28 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

t_env	*get_env_var(t_env *env, const char *name)
{
	if (!env || !name)
	{
		errno = EINVAL;
		return (NULL);
	}
	while (env->next)
	{
		if (ft_strncmp(env->name, name, -1) == 0)
			return (env);
		env = env->next;
	}
	if (ft_strncmp(env->name, name, -1) == 0)
		return (env);
	return (NULL);
}

t_env	*create_env_var(t_env *env, const char *name, const char *value,
														int visible)
{
	if (!env || !name)
	{
		errno = EINVAL;
		return (NULL);
	}
	while (env->next)
		env = env->next;
	if (!(env->next = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	env = env->next;
	env->name = ft_strdup(name);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	env->visible = visible;
	env->next = NULL;
	if (env->name == NULL)
		return (NULL);
	return (env);
}

int		change_env_var(t_env *env, const char *value, int visible)
{
	if (!env)
	{
		errno = EINVAL;
		return (-1);
	}
	if (value)
	{
		free(env->value);
		if (!value)
			env->value = NULL;
		else
			env->value = ft_strdup(value);
	}
	if (visible != -1)
		env->visible = visible;
	if (!env->value)
		return (-1);
	return (0);
}

int		set_pwd_env(t_env *env)
{
	t_env	*pwd;
	char	*gets_pwd;

	if (!(pwd = get_env_var(env, "PWD")))
	{
		gets_pwd = getcwd(NULL, 0);
		if (gets_pwd == NULL)
			return (-1);
		if (!(create_env_var(env, "PWD", gets_pwd, 0)))
			return (-1);
	}
	return (0);
}

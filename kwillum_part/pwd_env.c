/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 13:10:40 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 22:15:30 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	stop_process(t_data *data, int ret_code)
{
	if (need_fork(data))
	{
		clean_all(data);
		exit(ret_code);
	}
	return (ret_code);
}

int	ft_exit(t_data *data)
{
	int				len;
	unsigned char	res;

	if ((len = tab_len(data->params)) == 1)
		res = ft_atoi(get_env_var(data->env, "?")->value);
	else if (len == 2)
	{
		len = 0;
		while (ft_isdigit(data->params[1][len]))
			len++;
		if (data->params[1][len] && (res = 2))
			ft_putendl_fd("exit: numeric argument is required", STDERR_FILENO);
		else
			res = (unsigned char)ft_atoi(data->params[1]);
	}
	else
	{
		res = 1;
		ft_putendl_fd("exit: list of arguments is too big", STDERR_FILENO);
	}
	clean_all(data);
	exit(res);
	return ((int)res);
}

int	pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		set_errno(&data->error_notification, &data->error_status, errno);
		ft_putstr_fd("pwd: ", STDERR_FILENO);
		ft_putendl_fd(data->error_notification, STDERR_FILENO);
		free(path);
		return (stop_process(data, data->error_status));
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (stop_process(data, EXIT_SUCCESS));
}

int	env(t_data *data)
{
	t_env	*tmp;

	if (!data->env)
	{
		set_errno(&data->error_notification, &data->error_status, EFAULT);
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putendl_fd(data->error_notification, STDERR_FILENO);
		return (stop_process(data, EFAULT));
	}
	tmp = data->env;
	while (tmp)
	{
		if (tmp->visible == 3)
		{
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(tmp->value, STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
	return (stop_process(data, EXIT_SUCCESS));
}

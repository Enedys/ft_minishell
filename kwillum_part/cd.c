/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 23:07:15 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 22:48:45 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static int	invalid_number_of_arguments(t_data *data)
{
	data->error_notification = strerror(E2BIG);
	data->error_status = 1;
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putendl_fd(data->error_notification, STDERR_FILENO);
	if (need_fork(data))
	{
		clean_all(data);
		exit(1);
	}
	return (256);
}

static int	change_pwd_env(t_data *data)
{
	t_env	*pwd;
	t_env	*old;
	char	*tmp;
	int		res;

	res = 0;
	pwd = get_env_var(data->env, "PWD");
	if (!(old = get_env_var(data->env, "OLDPWD")))
		res = create_env_var(data->env, "OLDPWD", pwd->value, 3) ? 0 : -1;
	else
		res = change_env_var(old, pwd->value, -1);
	tmp = getcwd(NULL, 0);
	if (change_env_var(pwd, tmp, -1) == -1 || res == -1)
	{
		free(tmp);
		return (stop_process(data, EFAULT));
	}
	free(tmp);
	return (stop_process(data, EXIT_SUCCESS));
}

static int	jump_home(t_data *data, t_env *home_adress)
{
	home_adress = get_env_var(data->env, "HOME");
	if (!home_adress || !(home_adress->visible & 1))
	{
		data->error_status = 1;
		data->error_notification = "cd: HOME variable not set";
		ft_putendl_fd(data->error_notification, STDERR_FILENO);
		return (stop_process(data, 1));
	}
	else if ((chdir(home_adress->value)) == -1)
	{
		set_errno(&data->error_notification, &data->error_status, errno);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putendl_fd(data->error_notification, STDERR_FILENO);
		data->error_status = 1;
		return (stop_process(data, data->error_status));
	}
	return (0);
}

static int	jump_directory(t_data *data, int home)
{
	t_env	*home_adress;
	int		res;

	if (home)
	{
		home_adress = get_env_var(data->env, "HOME");
		res = jump_home(data, home_adress);
		if (res != 0)
			return (stop_process(data, res));
	}
	else
	{
		make_relative(&data->params[1], data);
		if ((chdir(data->params[1])) == -1)
		{
			set_errno(&data->error_notification, &data->error_status, errno);
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putendl_fd(data->error_notification, STDERR_FILENO);
			data->error_status = 1;
			return (stop_process(data, data->error_status));
		}
	}
	return (change_pwd_env(data));
}

int			cd(t_data *data)
{
	int	params_num;

	params_num = tab_len(data->params);
	if (params_num <= 0 || params_num > 2)
		return (invalid_number_of_arguments(data));
	else if (params_num == 1)
		return (jump_directory(data, HOME));
	else
		return (jump_directory(data, NOHOME));
}

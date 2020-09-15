/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_executable_child.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:36:39 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 19:33:18 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "../minishell.h"

static char			*create_exec_path(t_data *data, char *prefix,
					char *cmd_name)
{
	char	*tmp;
	int		res;

	if (!(tmp = (char *)ft_calloc(1, ft_strlen(cmd_name) +
	ft_strlen(prefix) + 2)))
	{
		clean_all(data);
		exit(errno);
	}
	res = ft_strlcpy(tmp, prefix, -1);
	tmp[res] = '/';
	tmp[res + 1] = '\0';
	ft_strlcat(tmp, cmd_name, -1);
	return (tmp);
}

int					exec_in_curr_dir(t_data *data, char *buf[2])
{
	int	err_num;

	err_num = errno;
	free(data->params[0]);
	free(data->command);
	make_relative(&buf[0], data);
	make_relative(&buf[1], data);
	data->params[0] = buf[1];
	data->command = buf[0];
	if (ft_strchr(data->params[0], '/') || ft_strchr(data->command, '/'))
	{
		execve(data->command, data->params, data->env_arr);
		err_num = errno;
	}
	ft_putstr_fd(data->command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(err_num), STDERR_FILENO);
	clean_all(data);
	exit(127);
}

void				clean_exit(t_data *data)
{
	clean_all(data);
	exit(errno);
}

int					exec_child_proccess(t_data *data)
{
	int		res;
	int		i;
	char	*buf[2];

	data->path_table = parse_path_var(data);
	buf[0] = ft_strdup(data->command);
	buf[1] = ft_strdup(data->params[0]);
	res = -1;
	i = 0;
	if (res == -1 && !ft_strrchr(data->command, '/'))
	{
		free(data->params[0]);
		if (!(data->params[0] = get_command_name(data->command, '/')))
			clean_exit(data);
		while (data->path_table && res == -1 && data->path_table[i])
		{
			free(data->command);
			data->command = create_exec_path(data, data->path_table[i],
					data->params[0]);
			res = execve(data->command, data->params, data->env_arr);
			i++;
		}
	}
	return (exec_in_curr_dir(data, buf));
}

int					execute(t_data *data)
{
	return (forking(data));
}

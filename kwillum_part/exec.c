/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 13:02:20 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 22:15:19 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static int		interpret_return_code(pid_t pid, int status, t_data *data)
{
	int	res;

	res = -1;
	if (pid)
	{
		if (WIFEXITED(status) && !WEXITSTATUS(status))
		{
			res = 0;
			set_errno(&data->error_notification, &data->error_status, 0);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status))
			set_errno(&data->error_notification, &data->error_status,
													WEXITSTATUS(status));
		else
			set_errno(&data->error_notification, &data->error_status, errno);
	}
	else
		set_errno(&data->error_notification, &data->error_status, errno);
	return (res);
}

static int		process_parent_process(t_data *data, pid_t child)
{
	pid_t	wait_pid;
	int		status;
	int		res;

	close_child_ends(data);
	init_signals(while_child);
	wait_pid = waitpid(child, &status, 0);
	init_signals(ignore);
	res = interpret_return_code(wait_pid, status, data);
	save_output_stream(data);
	close_parent_ends(data);
	return (res);
}

static int		process_child_process(t_data *data)
{
	init_signals(NULL);
	close_parent_ends(data);
	redirect_std_flows(data);
	close_child_ends(data);
	return (data->func(data));
}

static int		process_noforked_process(t_data *data)
{
	int	res;

	redirect_std_flows(data);
	res = data->func(data);
	res = interpret_return_code(1, res, data);
	close_child_ends(data);
	save_output_stream(data);
	close_parent_ends(data);
	return_std_flows(data);
	return (res);
}

int				forking(t_data *data)
{
	pid_t	child;

	if (!need_fork(data))
		return (process_noforked_process(data));
	child = fork();
	if (child == -1)
		return (set_errno(&data->error_notification,
							&data->error_status, errno));
	else if (child == 0)
		return (process_child_process(data));
	else
		return (process_parent_process(data, child));
	return (0);
}

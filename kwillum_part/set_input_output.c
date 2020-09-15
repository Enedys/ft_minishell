/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 20:42:14 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 13:44:08 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int				set_input_arrow(t_data *data)
{
	int	res;

	res = 0;
	if (data->buffer_end != -1)
		close(data->buffer_end);
	data->buffer_end = -1;
	close(data->read_tube[READ_END]);
	data->read_tube[READ_END] = open(data->redirect.file_read, O_RDONLY);
	if (data->read_tube[READ_END] == -1)
	{
		res = set_errno(&data->error_notification,
						&data->error_status, errno);
	}
	return (res);
}

int				set_input_pipe(t_data *data)
{
	if (data->buffer_end == -1)
	{
		close(data->read_tube[WRITE_END]);
		data->read_tube[WRITE_END] = -1;
		return (0);
	}
	close(data->read_tube[READ_END]);
	data->read_tube[READ_END] = data->buffer_end;
	return (0);
}

int				set_input_fd(t_data *data)
{
	if (data->redirect.l_arrow)
		return (set_input_arrow(data));
	else if (data->redirect.pipe_before)
		return (set_input_pipe(data));
	return (0);
}

int				set_output_fd(t_data *data)
{
	int	file_fd;
	int	mode;

	if (data->redirect.dr_arrow || data->redirect.r_arrow)
	{
		mode = O_WRONLY | O_CREAT | (data->redirect.dr_arrow == 1 ?
												O_APPEND : O_TRUNC);
		file_fd = open(data->redirect.file_write, mode, 0666);
		if (file_fd == -1)
		{
			set_errno(&data->error_notification,
							&data->error_status, errno);
			close(data->buffer_end);
			data->buffer_end = -1;
			return (-1);
		}
		close(data->write_tube[WRITE_END]);
		data->write_tube[WRITE_END] = file_fd;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 21:43:46 by Kwillum           #+#    #+#             */
/*   Updated: 2020/07/30 21:46:43 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int			close_child_ends(t_data *data)
{
	int	res;

	res = close(data->write_tube[WRITE_END]);
	if (close(data->read_tube[READ_END]) == -1 || res == -1)
		return (-1);
	return (0);
}

int			close_parent_ends(t_data *data)
{
	int	res;

	res = close(data->read_tube[WRITE_END]);
	if (close(data->write_tube[READ_END]) == -1 || res == -1)
		return (-1);
	return (0);
}

int			save_output_stream(t_data *data)
{
	if (data->redirect.pipe_after)
		data->buffer_end = data->write_tube[READ_END] == -1 ?
						-1 : dup(data->write_tube[READ_END]);
	return (data->buffer_end == -1 ? -1 : 0);
}

int			return_std_flows(t_data *data)
{
	int	res;
	int	res1;

	res = 0;
	res1 = 0;
	if (data->redirect.l_arrow || data->redirect.pipe_before)
		res = dup2(data->redirect.buf_stdin, STDIN_FILENO);
	if (data->redirect.dr_arrow || data->redirect.r_arrow
								|| data->redirect.pipe_after)
		res1 = dup2(data->redirect.buf_stdout, STDOUT_FILENO);
	return (res == -1 || res1 == -1 ? -1 : 0);
}

int			redirect_std_flows(t_data *data)
{
	int	res;
	int	res1;

	res = 0;
	res1 = 0;
	if (data->redirect.l_arrow || data->redirect.pipe_before)
	{
		data->redirect.buf_stdin = dup(STDIN_FILENO);
		res = dup2(data->read_tube[READ_END], STDIN_FILENO);
	}
	if (data->redirect.dr_arrow || data->redirect.r_arrow
								|| data->redirect.pipe_after)
	{
		data->redirect.buf_stdout = dup(STDOUT_FILENO);
		res1 = dup2(data->write_tube[WRITE_END], STDOUT_FILENO);
	}
	return (res == -1 || res1 == -1 ? -1 : 0);
}

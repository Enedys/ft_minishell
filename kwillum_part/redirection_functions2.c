/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_functions2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 00:11:31 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/05 21:58:33 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static t_list		*wr_app_args(t_list *lst, t_data *data)
{
	data->redirect.r_arrow = lst->type == WRITE ? 1 : 0;
	data->redirect.dr_arrow = lst->type == WRITE ? 0 : 1;
	lst = lst->next;
	lst->type = FILE;
	data->redirect.file_write = lst->data;
	data->redirect.wr_err = set_output_fd(data);
	return (lst);
}

static t_list		*rd_args(t_list *lst, t_data *data)
{
	data->redirect.l_arrow = 1;
	lst = lst->next;
	lst->type = FILE;
	data->redirect.file_read = lst->data;
	data->redirect.rd_err = set_input_arrow(data);
	return (lst);
}

int					get_args_num(t_list *lst, t_data *data)
{
	int	iter;

	iter = 0;
	while (lst && !is_cmdend(lst->type))
	{
		if (lst->type == WRITE || lst->type == APPEND)
			lst = wr_app_args(lst, data);
		else if (lst->type == READ)
			lst = rd_args(lst, data);
		else if (lst->type == ARG)
			iter++;
		lst = lst->next;
	}
	if (lst)
		data->redirect.pipe_after = lst->type == PIPE ? 1 : 0;
	if (!data->redirect.l_arrow)
		set_input_pipe(data);
	return (iter);
}

void				dump_redirections(t_data *data)
{
	int	pipe;

	pipe = data->redirect.pipe_after;
	ft_bzero(&data->redirect, sizeof(t_redirect));
	data->redirect.pipe_before = pipe;
	data->func = NULL;
	data->error_status = 0;
	data->error_notification = NULL;
	data->cmd_state = 0;
	data->command = NULL;
	data->params = NULL;
	data->path_table = NULL;
}

int					init_redirections(t_list *tmp, t_data *data)
{
	int	args;

	if (init_tubes(data) == -1)
		return ((data->cmd_state = -1));
	args = get_args_num(tmp, data);
	if (data->redirect.wr_err || data->redirect.rd_err)
	{
		close_child_ends(data);
		close_parent_ends(data);
		return ((data->cmd_state = -1));
	}
	if (!(data->params = (char **)malloc(sizeof(char *) * (args + 2))))
	{
		set_errno(&data->error_notification, &data->error_status, errno);
		close_child_ends(data);
		close_parent_ends(data);
		return ((data->cmd_state = -1));
	}
	return (0);
}

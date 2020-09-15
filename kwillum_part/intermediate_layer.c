/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intermediate_layer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:34:41 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/13 23:34:37 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "../minishell.h"

static int		cmd_process(char *str, t_data *data)
{
	const char	*cmds[] = {"cd", "pwd", "env", "echo", "unset",
										"export", "exit", NULL};
	int			(*func[9])(struct s_data *);
	int			i;

	i = 0;
	infill_func(func);
	data->params[0] = ft_strdup(str);
	data->command = ft_strdup(str);
	if (!data->command || !data->params[0])
	{
		set_errno(&data->error_notification, &data->error_status, ENOMEM);
		return ((data->cmd_state = -1));
	}
	while (cmds[i])
	{
		if (ft_strncmp(str, cmds[i], -1) == 0)
		{
			data->func = func[i];
			return (0);
		}
		i++;
	}
	data->func = func[i];
	return (0);
}

static int		load_param(t_data *data, int num, char *str)
{
	if (!(data->params[num] = ft_strdup(str)))
	{
		set_errno(&data->error_notification, &data->error_status, errno);
		data->cmd_state = -1;
		close_child_ends(data);
		close_parent_ends(data);
		return (-1);
	}
	return (0);
}

static t_list	*plot_cmd(t_data *data, t_list *tmp)
{
	int	args;

	dump_redirections(data);
	if ((args = init_redirections(tmp, data)) == -1)
		return (NULL);
	args = 1;
	while (tmp && !is_cmdend(tmp->type))
	{
		if (tmp->type == CMD && cmd_process(tmp->data, data) == -1)
			return (NULL);
		else if (tmp->type == ARG &&
				load_param(data, args++, tmp->data) == -1)
			return (NULL);
		tmp = tmp->next;
	}
	if (tmp)
		tmp = tmp->next;
	data->params[args] = NULL;
	return (tmp);
}

int				execute_and_clean(t_data *data)
{
	int	res;

	res = execute(data);
	clean_exec(data);
	return (res);
}

int				run_cmd(t_data *data)
{
	t_list	*tmp;
	int		res;

	res = 0;
	ft_bzero(&data->redirect, sizeof(t_redirect));
	data->buffer_end = -1;
	if (data->args == NULL)
	{
		dump_redirections(data);
		data->redirect.pipe_before = 0;
		return (0);
	}
	tmp = data->args;
	while ((tmp = plot_cmd(data, tmp)) && data->cmd_state == 0)
		res = execute_and_clean(data);
	if (data->cmd_state == 0)
		res = execute_and_clean(data);
	if (data->cmd_state == -1)
		ft_putendl_fd(data->error_notification, STDERR_FILENO);
	data->error_status = data->cmd_state < 0 ? 2 : data->error_status;
	data->cmd_state = res < data->cmd_state ? res : data->cmd_state;
	return (data->cmd_state);
}

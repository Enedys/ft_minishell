/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:14:09 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/13 20:14:32 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "../minishell.h"

int		init_tubes(t_data *data)
{
	int	res1;
	int	res2;

	data->read_tube[0] = -1;
	data->read_tube[1] = -1;
	data->write_tube[0] = -1;
	data->write_tube[1] = -1;
	data->redirect.buf_stdin = -1;
	data->redirect.buf_stdout = -1;
	if ((res1 = pipe(data->read_tube)) == -1)
	{
		set_errno(&data->error_notification, &data->error_status, errno);
		return (-1);
	}
	if ((res2 = pipe(data->write_tube)) == -1)
	{
		set_errno(&data->error_notification, &data->error_status, errno);
		close(data->read_tube[READ_END]);
		close(data->read_tube[WRITE_END]);
		return (-1);
	}
	return (0);
}

char	*get_command_name(const char *s, int sep)
{
	char	*tmp;
	char	*dup;

	if (!s)
		return (NULL);
	tmp = ft_strrchr(s, sep);
	if (tmp)
		dup = ft_strdup(tmp + 1);
	else
		dup = ft_strdup(s);
	return (dup);
}

int		need_fork(t_data *data)
{
	if (data->redirect.pipe_after || data->redirect.pipe_before
						|| data->func == exec_child_proccess)
		return (1);
	return (0);
}

int		set_errno(char **str, int *errno_pos, int err_num)
{
	*errno_pos = err_num;
	*str = strerror(err_num);
	return (-1);
}

int		tab_len(char **tab)
{
	int	iter;

	if (!tab)
		return (-1);
	iter = 0;
	while (tab[iter])
		iter++;
	return (iter);
}

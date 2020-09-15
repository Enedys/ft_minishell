/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:12:15 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/13 20:12:55 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "../minishell.h"

void			infill_func(int (**func)(struct s_data *))
{
	func[0] = cd;
	func[1] = pwd;
	func[2] = env;
	func[3] = ft_echo;
	func[4] = ft_unset;
	func[5] = ft_export;
	func[6] = ft_exit;
	func[7] = exec_child_proccess;
	func[8] = NULL;
}

char			**parse_path_var(t_data *data)
{
	char	**path_table;
	t_env	*path;

	path = get_env_var(data->env, "PATH");
	if (!path)
		return (NULL);
	path_table = ft_split(path->value, ':');
	return (path_table);
}

int				close_fd(int *fd)
{
	int	res;

	if (*fd == -1)
		return (-1);
	res = close(*fd);
	*fd = -1;
	return (res);
}

int				is_cmdend(int type)
{
	if (type == SEP || type == PIPE)
		return (1);
	return (0);
}

void			clean_exec(t_data *data)
{
	free(data->command);
	free_tab(data->params, -1);
	free_tab(data->path_table, -1);
}

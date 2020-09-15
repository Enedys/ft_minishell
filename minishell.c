/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:35:52 by walline           #+#    #+#             */
/*   Updated: 2020/08/20 02:00:36 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		clean_all(t_data *data)
{
	clean_exec(data);
	ft_delenv(&data->env);
	ft_delarr(data->env_arr);
	ft_delstr(data->line);
	ft_dellst(&data->tokens_free);
}

int			ft_minishell(t_data *data, int ac, char **av)
{
	ft_parseline(data);
	if (!ft_istokensvalid(data->args))
		return (1);
	ft_builtin_tolower(data);
	data->tokens = data->args;
	data->tokens_free = data->args;
	data->args = NULL;
	while (ft_getcmd(data))
	{
		if (!ft_getvariables(data, 0, 0))
			return (0);
		ft_replacevar(data);
		if (!ft_iscmdvalid(data->args))
			return (0);
		run_cmd(data);
	}
	(void)ac;
	(void)av;
	return (0);
}

void		ft_getcmdline(t_data *data, int *err)
{
	if (get_next_line(1, &data->line, 0) == -1)
	{
		*err = 2;
		process_interrupt(data);
		return ;
	}
	process_interrupt(data);
	while (!ft_isopenslash(data->line))
		if (ft_getaddline(data, 1, err, 0) == -1)
			return ;
	while ((ft_strcmp(ft_getchraddrend(data->line, '|'), \
		"|", 1)) && !*err)
		if (ft_getaddline(data, 2, err, 0) == -1)
			return ;
	while (!ft_isvalidquot(data->line))
		if (ft_getaddline(data, 0, err, 0) == -1)
			return ;
}

int			main(int ac, char **av, char **env)
{
	t_data	data;
	int		err;

	say_hello();
	data.state = 1;
	data.cmd_state = 0;
	init_signals(ignore);
	ft_createenvlst(&data, env);
	g_e_pwd = get_env_var(data.env, "PWD");
	data.env_arr = ft_getenvarr(data.env);
	while (data.state)
	{
		data.args = NULL;
		data.line = NULL;
		err = 0;
		refresh_status(&data);
		ft_getcmdline(&data, &err);
		if (err != 1 && data.line)
			err = ft_minishell(&data, ac, av);
		else if (err == 1)
			write(1, "-minishell: syntax error\n", 25);
		ft_delstr(data.line);
		ft_dellst(err == 1 ? &data.args : &data.tokens_free);
	}
	return (1);
}

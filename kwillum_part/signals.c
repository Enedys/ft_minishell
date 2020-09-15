/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:22:40 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/15 00:22:48 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "../minishell.h"

void	process_interrupt(t_data *data)
{
	char	*s;

	s = NULL;
	if (data->cmd_state != g_interrupt)
		change_env_var(get_env_var(data->env, "?"),\
			(s = ft_itoa(g_interrupt)), 0);
	free(s);
}

void	ignore(int sig)
{
	if (sig == 3)
	{
		g_interrupt = 131;
		return ;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	set_welcome();
	g_interrupt = 130;
}

void	while_child(int sig)
{
	if (sig == 2)
		ft_putchar_fd('\n', STDERR_FILENO);
	else
		ft_putendl_fd("Exit (core dumped)", STDERR_FILENO);
}

void	init_signals(void (*func)(int))
{
	signal(SIGINT, func);
	signal(SIGQUIT, func);
}

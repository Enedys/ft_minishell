/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:08:30 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 01:46:41 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void		set_welcome(void)
{
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
	if (g_interrupt == 0 || g_interrupt == 130 || g_interrupt == 131)
		ft_putstr_fd("\033[1;32m", STDOUT_FILENO);
	else
		ft_putstr_fd("\033[1;31m", STDOUT_FILENO);
	write(1, "minishell:", 10);
	ft_putstr_fd("\033[1;36m", STDOUT_FILENO);
	ft_putstr_fd(g_e_pwd->value, STDOUT_FILENO);
	ft_putstr_fd("$ ", STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
}

static void	say_hello1(void)
{
	ft_putstr_fd("\n	\033[38;5;45;48;5;255;1m*************", STDOUT_FILENO);
	ft_putstr_fd("*#**************#*************#*************", STDOUT_FILENO);
	ft_putstr_fd("#*************#\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("	\033[38;5;45;48;5;255;1m ______      # ___", STDOUT_FILENO);
	ft_putstr_fd("   ___     # ______      # __          # __ ", STDOUT_FILENO);
	ft_putstr_fd("         #\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("	\033[38;5;45;48;5;255;1m/_____/\\     #/__", STDOUT_FILENO);
	ft_putstr_fd("/\\ /__/\\    #/_____/\\     #/_/\\         ", STDOUT_FILENO);
	ft_putstr_fd("#/_/\\         #\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("	\033[38;5;45;48;5;255;1m\\:::: \\/     #", STDOUT_FILENO);
	ft_putstr_fd("\\::\\ \\\\  \\ \\   #\\::::_\\/_    #\\:", STDOUT_FILENO);
	ft_putstr_fd("\\ \\        #\\:\\ \\        #\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("	\033[104;38;5;255;1m \\:\\/___/\\   # \\::", STDOUT_FILENO);
	ft_putstr_fd("\\/_\\ .\\ \\  # \\:\\/___/\\   # \\:\\ \\  ", STDOUT_FILENO);
	ft_putstr_fd("     # \\:\\ \\       #\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("	\033[104;38;5;255;1m  \\_::._\\:\\  #  ", STDOUT_FILENO);
	ft_putstr_fd("\\:: ___::\\ \\ #  \\::___\\/_  #  \\:\\ ", STDOUT_FILENO);
	ft_putstr_fd("\\____  #  \\:\\ \\____  #\033[0m\n", STDOUT_FILENO);
}

static void	say_hello2(void)
{
	ft_putstr_fd("	\033[104;38;5;255;1m    /____\\:\\ #   ", STDOUT_FILENO);
	ft_putstr_fd("\\: \\ \\\\::\\ \\#   \\:\\____/\\ #   \\", STDOUT_FILENO);
	ft_putstr_fd(":\\/___/\\ #   \\:\\/___/\\ #\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("	\033[101;38;5;255;1m    \\_____\\/ #   ", STDOUT_FILENO);
	ft_putstr_fd(" \\__\\/ \\::\\/#    \\_____\\/ #    \\__", STDOUT_FILENO);
	ft_putstr_fd("___\\/ #    \\_____\\/ #\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("	\033[101;38;5;255;1m             ##   ", STDOUT_FILENO);
	ft_putstr_fd("           ##            ##            ", STDOUT_FILENO);
	ft_putstr_fd("##            ##\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("	\033[101;38;5;255;1m              ## ", STDOUT_FILENO);
	ft_putstr_fd("             ##            ##          ", STDOUT_FILENO);
	ft_putstr_fd("  ##            ##\033[0m\n", STDOUT_FILENO);
	ft_putstr_fd("							\033[1;35mby ", STDOUT_FILENO);
	ft_putstr_fd("Kwillum and Walline\n\033[0m\n", STDOUT_FILENO);
}

void		say_hello(void)
{
	say_hello1();
	say_hello2();
}

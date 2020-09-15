/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 21:25:14 by walline           #+#    #+#             */
/*   Updated: 2020/08/14 01:45:42 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_builtin_tolower(t_data *data)
{
	t_list	*t;
	char	*str;

	t = data->args;
	while (t)
	{
		if (t->type == CMD && !(ft_strcmp(t->data, "CD", 1) || \
		ft_strcmp(t->data, "Cd", 1) || ft_strcmp(t->data, "cD", 1)))
		{
			str = t->data;
			while (*str)
			{
				if (*str >= 'A' && *str <= 'Z')
					*str += 32;
				str++;
			}
		}
		t = t->next;
	}
}

void		refresh_status(t_data *data)
{
	t_env	*var;
	char	*str;

	if (data->cmd_state < 0)
		g_interrupt = data->error_status;
	else
		g_interrupt = 0;
	set_welcome();
	if (!(var = get_env_var(data->env, "?")))
		create_env_var(data->env, "?", (str = ft_itoa(g_interrupt)), 0);
	else
		change_env_var(var, (str = ft_itoa(g_interrupt)), 0);
	free(str);
}

int			ft_countslashbackward(char *str, int j)
{
	int		c;

	c = 0;
	while (j >= 0)
	{
		if (str[j] == '\\')
			c++;
		j--;
	}
	return (c % 2);
}

int			ft_dellstnode(t_data *data, t_list **lst)
{
	t_list	*prev;
	t_list	*next;

	next = (*lst)->next;
	prev = (*lst)->prev;
	free((*lst)->data);
	free(*lst);
	if (prev)
	{
		prev->next = next;
		return (1);
	}
	else
	{
		data->args = next;
		if (data->args)
			data->args->prev = NULL;
		return (0);
	}
}

int			ft_checkvar(char *data, int c)
{
	if (!((*data >= 'a' && *data <= 'z') || \
		(*data >= 'A' && *data <= 'Z')) && *data != '_')
	{
		write(1, "-minishell: ", 12);
		if (c == 0)
		{
			write(1, data, ft_strlen(data));
			write(1, ": command not found\n", 20);
		}
		if (c == 1)
		{
			write(1, "export: '", 9);
			write(1, data, ft_strlen(data));
			write(1, "': not a valid identifier\n", 26);
		}
		return (0);
	}
	return (1);
}

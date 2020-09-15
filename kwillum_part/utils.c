/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 20:04:42 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 19:34:05 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "../minishell.h"

void	*free_tab(char **tab, int final)
{
	int	iter;

	if (!tab)
		return (NULL);
	iter = 0;
	if (final < 0)
		final = 2147483647;
	while (tab[iter] && iter <= final)
	{
		free(tab[iter]);
		iter++;
	}
	free(tab);
	return (NULL);
}

void	print_error_status(t_data *data)
{
	ft_putnbr_fd(data->error_status, STDERR_FILENO);
	ft_putendl_fd(": ", STDERR_FILENO);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_putendl_fd(tab[i++], 1);
}

char	**copy_table(char **table)
{
	int		iter;
	char	**new_table;

	if (!table)
		return (NULL);
	iter = tab_len(table);
	if (!(new_table = (char **)malloc(sizeof(char *) * (iter + 1))))
		return (NULL);
	iter = 0;
	while (table[iter])
	{
		if (!(new_table[iter] = ft_strdup(table[iter])))
		{
			free_tab(new_table, iter);
			return (NULL);
		}
		iter++;
	}
	new_table[iter] = NULL;
	return (new_table);
}

void	make_relative(char **str, t_data *data)
{
	t_env	*home_adress;
	char	*tmp;

	if (**str == '~')
	{
		home_adress = get_env_var(data->env, "HOME");
		if (home_adress)
		{
			tmp = ft_strjoin(home_adress->value, *str + 1);
			if (!tmp)
				return ;
			free(*str);
			*str = tmp;
		}
	}
}

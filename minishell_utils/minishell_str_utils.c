/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_str_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:41:16 by walline           #+#    #+#             */
/*   Updated: 2020/08/14 01:47:05 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"

char			*ft_strappend(char *s1, char *s2)
{
	char		*str;
	int			len1;
	int			len2;
	char		*result;

	if (!s1 && !s2)
		return (NULL);
	if (!(s1) || !(s2))
		return (!(s1) ? s2 : s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	result = str;
	while (*s1)
		*str++ = *s1++;
	ft_delstr(s1 - len1);
	while (*s2)
		*str++ = *s2++;
	ft_delstr(s2 - len2);
	*str = '\0';
	return (result);
}

static int		ft_create_new_line(char **fd_arr, char **line, char *nl_addr)
{
	char		*temp;

	*nl_addr++ = '\0';
	*line = ft_strdup(*fd_arr);
	if (*nl_addr == '\0')
	{
		free(*fd_arr);
		*fd_arr = NULL;
		return (1);
	}
	temp = ft_strdup(nl_addr);
	free(*fd_arr);
	*fd_arr = temp;
	return (1);
}

static int		ft_process_output(char **fd_arr, char **line, int ret)
{
	char		*nl_addr;

	if (ret < 0)
		return (-1);
	if (*fd_arr && (nl_addr = ft_strchr(*fd_arr, '\n')))
		return (ft_create_new_line(fd_arr, line, nl_addr));
	if (*fd_arr)
	{
		*line = *fd_arr;
		*fd_arr = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

static int		gnl_util(int ret, char **line, int flag, char **fd_arr)
{
	if (ret == 0 && flag == 0)
	{
		write(1, "exit\n", 5);
		*line = ft_strdup("exit");
		return (-1);
	}
	else if (ret == 0)
	{
		write(1, "\n", 1);
		*line = NULL;
		ft_delstr(*fd_arr);
		*fd_arr = NULL;
		return (-1);
	}
	return (1);
}

int				get_next_line(int fd, char **line, int flag)
{
	static char	*fd_arr[10];
	char		buff[1024];
	int			ret;
	char		*nl_addr;

	while ((ret = read(fd, buff, 1)) >= 0)
	{
		if (gnl_util(ret, line, flag, &fd_arr[fd]) < 0)
			return (-1);
		flag = 1;
		buff[ret] = '\0';
		fd_arr[fd] = ft_strappend(fd_arr[fd], ft_strdup(buff));
		if ((nl_addr = ft_strchr(fd_arr[fd], '\n')))
			return (ft_create_new_line(&fd_arr[fd], line, nl_addr));
		if (g_interrupt == 130 || g_interrupt == 131)
		{
			get_next_line(fd, line, 1);
			return (-1);
		}
	}
	if (ret == -1)
		exit(EXIT_FAILURE);
	return (ft_process_output(&fd_arr[fd], line, ret));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:42:53 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/14 01:43:47 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define WRITE_END 1
# define READ_END 0
# define HOME 1
# define NOHOME 0

# define BUF 4096
# define SEP 1
# define PIPE 2
# define WRITE 3
# define READ 4
# define APPEND 5
# define CMD 6
# define ARG 7
# define VAR 8
# define FILE 9

typedef struct		s_list
{
	char			*data;
	int				type;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct		s_redirect
{
	char			pipe_before;
	char			pipe_after;
	char			l_arrow;
	char			r_arrow;
	char			dr_arrow;
	char			*file_read;
	char			*file_write;
	int				buf_stdin;
	int				buf_stdout;
	int				wr_err;
	int				rd_err;
}					t_redirect;

typedef struct		s_env
{
	char			*name;
	char			*value;
	char			visible;
	struct s_env	*next;

}					t_env;

typedef struct		s_data
{
	int				cmd_state;
	int				error_status;
	char			*error_notification;
	char			**path_table;
	t_redirect		redirect;
	t_env			*env;
	int				read_tube[2];
	int				write_tube[2];
	int				buffer_end;
	int				(*func)(struct s_data *);
	char			*command;
	char			**params;
	pid_t			pid;

	char			**env_arr;
	char			*line;
	int				state;
	t_list			*args;
	t_list			*tokens;
	t_list			*tokens_free;
}					t_data;

int					g_interrupt;
t_env				*g_e_pwd;
int					ft_checkvar(char *data, int c);

#endif

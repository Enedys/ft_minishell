/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:18:29 by Kwillum           #+#    #+#             */
/*   Updated: 2020/08/15 00:19:14 by Kwillum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../structures.h"
# include <fcntl.h>
# include <signal.h>

/*
** functions provides connection between kwillum and walline parts
*/
int				run_cmd(t_data *data);
void			clean_exec(t_data *data);
void			clean_all(t_data *data);
int				is_cmdend(int type);
int				get_args_num(t_list *lst, t_data *data);
void			dump_redirections(t_data *data);
int				init_redirections(t_list *tmp, t_data *data);
void			while_child(int sig);
void			ignore(int sig);
void			init_signals(void (*func)(int));
void			say_hello(void);

/*
** functions located in utils.c and not sorted yet
*/
int				need_fork(t_data *data);
int				init_tubes(t_data *data);
char			*get_command_name(const char *s, int sep);
int				set_errno(char **str, int *errno_pos, int err_num);
int				tab_len(char **tab);
int				stop_process(t_data *data, int ret_code);
void			*free_tab(char **tab, int final);
void			make_relative(char **str, t_data *data);
void			process_interrupt(t_data *data);

/*
** trash/test functions (utils.c)
*/
void			print_tab(char **tab);
void			print_error_status(t_data *data);
char			**copy_table(char **table);

/*
** fuctions needed for execute (exec.c)
*/
int				execute(t_data *data);
int				forking(t_data *data);
void			infill_func(int (**func)(struct s_data *));
char			**parse_path_var(t_data *data);
void			set_welcome(void);

int				set_input_arrow(t_data *data);
int				set_input_pipe(t_data *data);
int				set_input_fd(t_data *data);
int				set_output_fd(t_data *data);

int				env(t_data *data);
int				cd(t_data *data);
int				pwd(t_data *data);
int				ft_exit(t_data *data);
int				exec_child_proccess(t_data *data);

int				close_child_ends(t_data *data);
int				close_parent_ends(t_data *data);
int				redirect_std_flows(t_data *data);
int				save_output_stream(t_data *data);
int				return_std_flows(t_data *data);

/*
** functions for linked list processing of env variables
*/
t_env			*get_env_var(t_env *env, const char *name);
t_env			*create_env_var(t_env *env, const char *name,
								const char *value, int visible);
int				change_env_var(t_env *env, const char *value,
													int visible);
int				set_pwd_env(t_env *env);
t_env			*load_env(t_env *start);

#endif

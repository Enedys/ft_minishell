/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:42:00 by walline           #+#    #+#             */
/*   Updated: 2020/08/13 21:14:43 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V2_MINISHELL_UTILS_H
# define MINISHELL_V2_MINISHELL_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>

# include "../structures.h"
# include "../libft/libft.h"

void		ft_printarr(char **arr);
void		ft_delenv(t_env **lst);
t_env		*ft_createenv(char *str, int visible);
char		**ft_getenvarr(t_env *lst);
void		ft_delarr(char **arr);
void		ft_printsortedenv(char **arr, int i, int j);
int			ft_countarrlen(char **arr);
int			ft_countenv(t_env *lst);
char		**ft_arraddback(char **arr, char *str);
int			ft_export(t_data *data);
char		**ft_arrdelstr(char **arr, int index);
int			ft_unset(t_data *data);
int			ft_echo(t_data *data);
int			ft_isctoken(int i);
void		ft_delsep(t_data *data);
int			*ft_get_invalid_arg_index_arr(char **data);
int			ft_arrnum(int *arr, int num, int len);
int			ft_findvararr(char *str, char **arr, int i, int j);
void		env_support(t_data *data, int i);
int			ft_recquot(char *str, int i);
void		ft_lstadd_back(t_list **alst, t_list *new);
t_list		*ft_lstnew(void *content);
void		ft_dellst(t_list **lst);
void		ft_envlstadd_back(t_env **alst, t_env *new);
t_env		*ft_envlstnew(char *name, char *value, int visible);
int			ft_strcmp(const char *s1, const char *s2, int prec);
int			get_next_line(int fd, char **line, int flag);
char		*ft_strappend(char *s1, char *s2);
int			ft_countwords(char *str);
char		*ft_getchraddrend(char *str, int c);
char		*ft_getchraddr(char *str, int c);
void		ft_delstr(char *str);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kwillum <daniilxod@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:35:45 by walline           #+#    #+#             */
/*   Updated: 2020/08/14 00:20:24 by walline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_V2_MINISHELL_H
# define MINISHELL_V2_MINISHELL_H

# include "./minishell_utils/minishell_utils.h"
# include "./kwillum_part/includes.h"

void		ft_parseline(t_data *data);
void		ft_recargtypes(t_list *temp, int f, char *str);
char		*ft_processline(char *str, int i, int j);
int			ft_recquot(char *str, int i);
int			ft_isvalidquot(char *s);
int			ft_iscmdvalid(t_list *l);
int			ft_varcmp(const char *s1, const char *s2);
void		ft_replacevar(t_data *data);
int			ft_getcmd(t_data *data);
int			ft_isopenslash(char *str);
int			ft_istoken(char *line, int i);
int			ft_isslashquot(char *str, int i);
int			ft_takequot(char *str, int i);
void		ft_deleteescapes(char **str, char *temp, int i, char *s);
int			ft_countslashbackward(char *str, int j);
t_env		*ft_findvar(char *str, t_env *var);
int			ft_getaddline(t_data *data, int slash, int *err, char *t);
void		ft_createenvlst(t_data *data, char **env);
t_env		*ft_createenv(char *str, int visible);
int			ft_getvariables(t_data *data, t_list *temp, char *s);
char		*ft_getresultstr(t_data *data, char *str);
char		*ft_getvarvalue(t_data *data, char *str, int *i);
int			ft_istokensvalid(t_list *l);
void		refresh_status(t_data *data);
void		ft_builtin_tolower(t_data *data);
int			ft_dellstnode(t_data *data, t_list **lst);
int			ft_countslashbackward(char *str, int j);

#endif

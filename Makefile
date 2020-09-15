# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: walline <walline@student.21-school.ru>     +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2020/08/13 23:50:33 by walline           #+#    #+#             #
#   Updated: 2020/08/14 00:03:05 by walline          ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME = minishell

SRC = minishell.c parser.c features.c variables.c welcome_status.c minishell_utils/var_utils_2.c minishell_utils/str_utils.c minishell_utils/minishell_utils_2.c minishell_utils/echo_export_unset.c minishell_utils/minishell_lst_utils.c minishell_utils/parser_utils_2.c minishell_utils/minishell_utils.c minishell_utils/utils.c minishell_utils/minishell_str_utils.c minishell_utils/libft.c minishell_utils/var_utils.c minishell_utils/parser_utils_1.c kwillum_part/utils2.c kwillum_part/redirection_functions.c kwillum_part/exec.c kwillum_part/intermediate_layer.c kwillum_part/utils1.c kwillum_part/env_list_functions.c kwillum_part/utils.c kwillum_part/redirection_functions2.c kwillum_part/visual_func.c kwillum_part/cd.c kwillum_part/process_executable_child.c kwillum_part/pwd_env.c kwillum_part/signals.c kwillum_part/set_input_output.c

INCLUDES = -I minishell.h structures.h kwillum_part/includes.h minishell_utils/minishell_utils.h

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@gcc $(FLAGS) $(OBJ) ./libft/libft.a -o $(NAME)
	@echo "Compiled!"

libft/libft.a:
	@make -C libft

clean:
	@rm -rf $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all
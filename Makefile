# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bandre <bandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/07 16:17:12 by bandre            #+#    #+#              #
#    Updated: 2018/04/17 21:17:13 by bandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = minishell_src

OBJ_PATH = minishell_obj

SRC = minishell.o\
	  execute_binary.o\
	  env.o\
	  utils.o\
	  cd.o\
	  echo.o\
	  exit.o\

CC = gcc -g 

FLAG = -Wall -Wextra -Werror -O

LIB = libft/libftprintf.a libft_chained_list/libft_chained_list.a

SRC_O = $(addprefix $(OBJ_PATH)/,$(SRC))

all: EXEC $(NAME)

$(NAME): $(SRC_O)
	$(CC) $(FLAG) -o $(NAME) $(SRC_O) $(LIB)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) -c $< -o $@ $(FLAG)

EXEC:
	make -C libft/
	make -C libft_chained_list/

clean:
	rm -f $(addprefix $(OBJ_PATH)/,$(SRC))
	make -C libft clean
	make -C libft_chained_list clean
	

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C libft_chained_list fclean


re: fclean all

flag: $(SRC)
	$(CC) $(NAME) $(LIB) -o $(NAME)

do: all
	./malloc

.PHONY: $(NAME) all %.o clean fclean re flag EXEC

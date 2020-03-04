# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbrophy <dbrophy@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 10:38:40 by dbrophy           #+#    #+#              #
#    Updated: 2020/02/26 10:41:22 by dbrophy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -I. -c -g
NAME=libftprintf.a
OBJ=$(SRC:.c=.o)
SRC=	ft_printf.c \
		printf_chrs.c \
		printf_fill.c \
		printf_handle_percent.c \
		printf_nbrs.c \
		printf_strs.c \
		logtool.c


$(NAME): 
	$(CC) $(CFLAGS) $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


FLAGS=-Wall -Wextra -Werror -O3
NAME=libftprintf.a

$(NAME): 
	gcc $(FLAGS) ft_printf.c -c -o ft_printf.c.o
	gcc $(FLAGS) printf_chrs.c -c -o printf_chrs.c.o
	gcc $(FLAGS) printf_handle_percent.c -c -o printf_handle_percent.c.o
	gcc $(FLAGS) printf_nbrs.c -c -o printf_nbrs.c.o
	gcc $(FLAGS) printf_strs.c -c -o printf_strs.c.o
	
	ar rcs $(NAME) ft_printf.c.o printf_chrs.c.o printf_handle_percent.c.o printf_nbrs.c.o printf_strs.c.o

all: $(NAME)

clean: 
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all


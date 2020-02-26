FLAGS=-Wall -Wextra -Werror -O3
NAME=libftprintf.a

$(NAME): 
	gcc $(FLAGS) ft_printf.c -c -o ft_printf.c.o
	
	ar rcs $(NAME) ft_printf.c.o

all: $(NAME)

clean: 
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all


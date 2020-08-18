NAME = lem-in

SRCS = 	srcs/main.c \
		srcs/read_input.c \
		srcs/bfs.c

OBJS = 	main.o \
		read_input.o \
		bfs.o

INCS = -I ./srcs -I ./libft/includes/

CFLAGS = -g -Wall -Wextra -Werror

LIB = -L./libft -lft

HEADER	= includes/

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(CFLAGS) -c $(SRCS) $(INCS)
	gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) -o $(NAME)

debug:

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

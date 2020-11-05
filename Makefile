NAME = lem-in

SRCS = 	srcs/main.c \
		srcs/read_input_basics.c \
		srcs/read_input_rooms.c \
		srcs/read_input_links.c \
		srcs/solve.c \
		srcs/hash.c \
		srcs/send_ants.c \
		srcs/print_info.c \
		srcs/inits.c 

OBJS = 	main.o \
		read_input_basics.o \
		read_input_rooms.o \
		read_input_links.o \
		solve.o \
		hash.o \
		send_ants.o \
		print_info.o \
		inits.o

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

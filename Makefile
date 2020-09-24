NAME = lem-in

SRCS = 	srcs/main.c \
		srcs/read_input_basics.c \
		srcs/read_input_rooms.c \
		srcs/read_input_links.c \
		srcs/bfs.c \
		srcs/hash.c \
		srcs/visualiser.c \
		srcs/inits.c 

OBJS = 	main.o \
		read_input_basics.o \
		read_input_rooms.o \
		read_input_links.o \
		bfs.o \
		hash.o \
		visualiser.o \
		inits.o

INCS = -I ./srcs -I ./libft/includes/

CFLAGS = -g -Wall -Wextra -Werror

LIB = -L./libft -lft

SDL2 = -L lib -l SDL2-2.0.0

HEADER	= includes/

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(CFLAGS) -c $(SRCS) $(INCS)
	gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) $(SDL2) -o $(NAME)

debug:

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

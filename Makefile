NAME = lem-in

SRCS = 	srcs/main.c \
		srcs/input/read_input_basics.c \
		srcs/input/read_input_rooms.c \
		srcs/input/read_input_links.c \
		srcs/input/hash.c \
		srcs/input/flags.c \
		srcs/input/check_rooms.c \
		srcs/algo/solve.c \
		srcs/algo/edmondskarp.c \
		srcs/algo/send_ants.c \
		srcs/utils/print_info.c \
		srcs/utils/inits.c \
		srcs/utils/utils.c \
		srcs/utils/free.c

INCS = -I ./includes -I ./libft/includes/

CFLAGS = -g -Wall -Wextra -Werror

LIB = -L ./libft -lft

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(CFLAGS) -o $(NAME) $(SRCS) $(INCS) $(LIB)

.PHONY: clean fclean re all

clean:
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

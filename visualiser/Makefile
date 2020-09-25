NAME = visu

SRCS = 	main.c \

OBJS = 	main.o

CFLAGS = -g -Wall -Wextra -Werror

SDL2 = -L lib -l SDL2-2.0.0

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -c $(SRCS)
	gcc $(CFLAGS) $(OBJS) $(SDL2) -o $(NAME)

debug:

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

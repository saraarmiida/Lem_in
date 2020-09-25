NAME = visu

SRCS = 	main.c \

OBJS = 	main.o

CFLAGS = -g -Wall -Wextra -Werror

LIB = -L ../libft -lft

SDL2 = -L lib -l SDL2-2.0.0

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -c $(SRCS)
	gcc $(CFLAGS) $(OBJS) $(SDL2) $(LIB) -o $(NAME)

debug:

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

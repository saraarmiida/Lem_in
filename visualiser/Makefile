NAME = visu

SRCS = srcs/main.c

INC = /Users/spentti/.brew/Cellar/sdl2/2.0.12_1/include

LIB = /Users/spentti/.brew/Cellar/sdl2/2.0.12_1/lib

all: $(NAME)

$(NAME):
	clang srcs/main.c -I $(INC) -L $(LIB) -lSDL2 -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
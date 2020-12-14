NAME = visu
FILES = main.c inits.c draw_cmds.c draw_cmds_more.c
LIB = ../libft/libft/libft.a
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	@make -C ../libft/libft
	gcc -g -Wall -Wextra -Werror -framework SDL2 -framework SDL2_ttf -F ./ $(FILES) $(LIB) -o $(NAME) -rpath @executable_path

clean:
	@make clean -C ../libft/libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C ../libft/libft

re: fclean
	make all
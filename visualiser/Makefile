NAME = visu
FILES = main.c draw_nodes.c draw_lines.c draw_text.c
LIB = ../libft/libft.a
INCLUDE = ../libft/ft_printf/includes
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	@make -C ../libft
	gcc -g -Wall -Wextra -Werror -framework SDL2 -framework SDL2_ttf -F ./ $(FILES) $(LIB) -I $(INCLUDE) -o $(NAME) -rpath @executable_path

clean:
	@make clean -C ../libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C ../libft

re: fclean
	make all
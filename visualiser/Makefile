# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spentti <spentti@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 13:13:57 by tlouekar          #+#    #+#              #
#    Updated: 2020/12/15 13:57:56 by spentti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visu
FILES = main.c inits.c draw_cmds.c draw_cmds_more.c
LIB = ../libft/libft/libft.a
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	@make -C ../libft/libft
	gcc -Wall -Wextra -Werror -framework SDL2 -framework SDL2_ttf -F ./ $(FILES) $(LIB) -o $(NAME) -rpath @executable_path

clean:
	@make clean -C ../libft/libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C ../libft/libft

re: fclean
	make all
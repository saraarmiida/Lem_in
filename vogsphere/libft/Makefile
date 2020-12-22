# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spentti <spentti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 14:03:19 by spentti           #+#    #+#              #
#    Updated: 2020/02/24 14:28:47 by spentti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIBNAME = libft.a

LIBFT = libft

FLAGS = -Wall -Wextra -Werror

INC = ft_printf/includes/ft_printf.h

SRC = ft_printf/srcs/c_char.c \
		ft_printf/srcs/c_double.c \
		ft_printf/srcs/c_hex.c \
		ft_printf/srcs/c_int.c \
		ft_printf/srcs/c_octal.c \
		ft_printf/srcs/c_pointer.c \
		ft_printf/srcs/c_unsigned.c \
		ft_printf/srcs/c_binary.c \
		ft_printf/srcs/conversions.c \
		ft_printf/srcs/ft_printf.c \
		ft_printf/srcs/modifiers.c \
		ft_printf/srcs/parse_format.c \
		ft_printf/srcs/utils.c \
		ft_printf/srcs/ft_ftoa.c

OBJ = c_char.o \
		c_double.o \
		c_hex.o \
		c_int.o \
		c_octal.o \
		c_pointer.o \
		c_unsigned.o \
		c_binary.o \
		conversions.o \
		ft_printf.o \
		modifiers.o \
		parse_format.o \
		utils.o \
		ft_ftoa.o

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ):
	@gcc $(FLAGS) -c $(SRC) -I $(INC)

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
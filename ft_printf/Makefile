# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 23:27:25 by mkneisl           #+#    #+#              #
#    Updated: 2025/02/25 15:27:51 by mkneisl          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIB = libft.a
FILES = ft_itoa_sb.o ft_itoa_ub.o ft_printf_util.o ft_printf_parse.o ft_printf.o
HEADER = libft.h ft_printf.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADER)
	@cc -c $< $(FLAGS)

$(NAME): $(FILES)
	@make -C ../libft/ $(LIB)
	@ar rc ../libft/$(LIB) $(FILES)

clean:
	@make -C ../libft/ clean
	@rm -f $(FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 13:24:54 by mkneisl           #+#    #+#              #
#    Updated: 2025/03/26 17:34:39 by mkneisl          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

BIN = bin
DIR_GUARD=@mkdir -p $(@D)

CORE_FILES= ft_atoi	\
			ft_bzero \
			ft_calloc\
			ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_isprint \
			ft_itoa \
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memmove \
			ft_memset \
			ft_putchar_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_putstr_fd \
			ft_split \
			ft_strchr \
			ft_strdup \
			ft_striteri \
			ft_strjoin \
			ft_strlcat \
			ft_strlcpy \
			ft_strlen \
			ft_strmapi \
			ft_strncmp \
			ft_strnstr \
			ft_strrchr \
			ft_strtrim \
			ft_substr \
			ft_tolower \
			ft_toupper \
			ft_lstadd_back \
			ft_lstadd_front \
			ft_lstclear \
			ft_lstdelone \
			ft_lstiter \
			ft_lstlast \
			ft_lstnew \
			ft_lstsize \
			ft_lstmap 

FTPRINTF_FILES = 	ft_printf \
					ft_itoa_sb \
					ft_itoa_ub \
					ft_printf_util \
					ft_printf_parse

OBJ_FILES = $(addprefix $(BIN)/core/, $(addsuffix .o , $(CORE_FILES)))
OBJ_FILES += $(addprefix $(BIN)/ft_printf/, $(addsuffix .o , $(FTPRINTF_FILES)))
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(BIN)/%.o: ./%.c
	@$(DIR_GUARD)
	cc -c $< $(CFLAGS) -Iinclude  -o $@

$(NAME): $(OBJ_FILES)
	ar rc $(NAME) $(OBJ_FILES)

clean:
	@rm -rf $(BIN)

fclean: clean
	@rm -f $(NAME)

re: fclean all
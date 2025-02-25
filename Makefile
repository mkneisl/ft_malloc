BIN = bin

FILE_NAMES = malloc_intrnl \
			ft_malloc \
			show_alloc
OBJ_FILES = $(addprefix $(BIN)/, $(addsuffix .o , $(FILE_NAMES)))
LIBFT=./libft/libft.a

CFLAGS = -Werror -Wall -Wextra -g # -fsanitize=address

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME=libft_malloc_$(HOSTTYPE).so
LINK_NAME=libft_malloc.so
DIR_GUARD=@mkdir -p $(@D)

all: $(NAME)

$(BIN)/%.o: ./src/%.c
	$(DIR_GUARD)
	cc -c $< $(CFLAGS) -o $@

$(NAME): $(OBJ_FILES)
	make -C ./ft_printf/ 
	mv $(LIBFT) ./$(BIN)/$(NAME)
	ar rc ./$(BIN)/$(NAME) $(OBJ_FILES)
	ln -f -s ./$(BIN)/$(NAME) $(LINK_NAME)
	cc -g $(CFLAGS) ./tests/main.c $(LINK_NAME) -o a.out


clean:
	rm -f $(OBJ_FILES)

fclean:
	rm -f $(NAME)
	rm -f $(LINK_NAME)
	rm -rf $(BIN)

re: fclean $(NAME)

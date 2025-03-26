BIN = bin

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CFLAGS = -Werror -Wall -Wextra -fPIC
FILE_NAMES = malloc_intrnl \
			ft_malloc \
			show_alloc \
			show_alloc_ex \
			print_util \
			chunk	\
			lrg_chunk \
			zone
OBJ_FILES = $(addprefix $(BIN)/, $(addsuffix .o , $(FILE_NAMES)))
LIBFT=./libft/libft.a

NAME=$(BIN)/libft_malloc_$(HOSTTYPE).so
LINK_NAME=libft_malloc.so
DIR_GUARD=@mkdir -p $(@D)

all: $(NAME)

$(BIN)/%.o: ./src/%.c
	$(DIR_GUARD)
	cc -c $< $(CFLAGS) -Ilibft/include -o $@

$(NAME): $(OBJ_FILES) $(LIBFT)
	cc -shared $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	ln -f -s $(NAME) $(LINK_NAME)

malloc-test:
	cc $(CFLAGS) ./tests/main.c -L. -Ilibft/include -lft_malloc -o $@

$(LIBFT):
	make -C ./libft/

clean:
	rm -f malloc-test
	rm -f $(OBJ_FILES)
	make -C ./libft/ clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LINK_NAME)
	rm -rf $(BIN)
	make -C ./libft/ fclean

re: fclean $(LINK_NAME)

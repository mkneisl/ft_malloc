BIN = bin

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CFLAGS = -Werror -Wall -Wextra -fPIC -g
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

NAME=libft_malloc_$(HOSTTYPE).so
LINK_NAME=libft_malloc.so
DIR_GUARD=@mkdir -p $(@D)

all: $(LINK_NAME)

$(BIN)/%.o: ./src/%.c
	$(DIR_GUARD)
	cc -c $< $(CFLAGS) -o $@

$(LINK_NAME): $(OBJ_FILES) $(LIBFT)
	cc  -fPIC -shared $(OBJ_FILES) $(LIBFT) -o ./$(BIN)/$(NAME)
	ln -f -s ./$(BIN)/$(NAME) $(LINK_NAME)
	cc $(CFLAGS) ./tests/main.c -L. -lft_malloc -o a.out

$(LIBFT):
	make -C ./ft_printf/

clean:
	rm -f $(OBJ_FILES)
	make -C ./ft_printf/ clean

fclean:
	rm -f $(NAME)
	rm -f $(LINK_NAME)
	rm -rf $(BIN)
	make -C ./ft_printf/ fclean

re: fclean $(LINK_NAME)

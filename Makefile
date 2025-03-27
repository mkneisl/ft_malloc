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
TEST_FILES =	avrgTests \
				memIntegrity \
				zoneAllocCount
OBJ_FILES = $(addprefix $(BIN)/, $(addsuffix .o , $(FILE_NAMES)))
TESTERS = $(addprefix tests/, $(addsuffix .out , $(TEST_FILES)))
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

./tests/%.out: ./tests/%.c
	cc $(CFLAGS) $< -L. -Ilibft/include -Iinclude -lft_malloc -o $@

tests: $(TESTERS)

$(LIBFT):
	make -C ./libft/

clean:
	rm -f malloc-test
	rm -f $(OBJ_FILES)
	rm -f $(TESTERS)
	make -C ./libft/ clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LINK_NAME)
	rm -rf $(BIN)
	make -C ./libft/ fclean

re: fclean $(NAME)

NAME=libft_malloc.so
BIN = bin


FILE_NAMES = malloc_intrnl \
			ft_malloc 
OBJ_FILES = $(addprefix $(BIN)/, $(addsuffix .o , $(FILE_NAMES)))


CFLAGS = -Werror -Wall -Wextra

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
LIB_NAME=libft_malloc_$(HOSTTYPE).so
DIR_GUARD=@mkdir -p $(@D)

all: $(NAME)

$(BIN)/%.o: ./src/%.c
	$(DIR_GUARD)
	cc -c $< $(CFLAGS) -o $@

$(NAME): $(OBJ_FILES)
	ar rc ./$(BIN)/$(LIB_NAME) $(OBJ_FILES)
	ln -s ./$(BIN)/$(LIB_NAME) $(NAME)
	cc -g $(CFLAGS) ./tests/main.c $(NAME) -o a.out


clean:
	rm -f $(OBJ_FILES)

fclean:
	rm -f $(NAME)
	rm -rf $(BIN)

re: fclean $(NAME)

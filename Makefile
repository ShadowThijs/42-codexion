NAME = codexion

CC = cc
FLAGS = -g -Wall -Werror -Wextra -I./include
INCLUDE = include
SOURCE = src

SOURCE_FILES = $(shell find $(SOURCE) -name '*.c')
SOURCE_OBJECTS = $(SOURCE_FILES:.c=.o)

# extra checks (no -Werror, so noisy warnings don't block you)
STRICT = -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
         -Wformat=2 -Wnull-dereference -g -I./$(INCLUDE)

$(SOURCE)/%.o: $(SOURCE)/%.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SOURCE_OBJECTS)
	@$(CC) $(FLAGS) $(SOURCE_OBJECTS) -lpthread -o $(NAME)

# static analysis (GCC only), no binary produced
analyze:
	@for f in $(SOURCE_FILES); do \
		gcc $(STRICT) -O1 -fanalyzer -c $$f -o /dev/null || exit 1; \
	done

# ASan + UBSan + LeakSanitizer
asan:
	@$(CC) $(STRICT) -fsanitize=address,undefined -fno-omit-frame-pointer \
		$(SOURCE_FILES) -lpthread -o $(NAME)_asan

# data races (can't be combined with ASan)
tsan:
	@$(CC) $(STRICT) -fsanitize=thread \
		$(SOURCE_FILES) -lpthread -o $(NAME)_tsan

clean:
	@rm -f $(SOURCE_OBJECTS)

fclean: clean
	@rm -f $(NAME) $(NAME)_asan $(NAME)_tsan

re: fclean all

.PHONY: all clean fclean re analyze asan tsan
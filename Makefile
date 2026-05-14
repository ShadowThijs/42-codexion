NAME = codexion

CC = cc
FLAGS = -g -Wall -Werror -Wextra -I./include
INCLUDE = include
SOURCE = src

SOURCE_FILES = $(shell find $(SOURCE) -name '*.c')
SOURCE_OBJECTS = $(SOURCE_FILES:.c=.o)

$(SOURCE)/%.o: $(SOURCE)/%.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SOURCE_OBJECTS)
	@$(CC) $(FLAGS) $(SOURCE_OBJECTS) -lpthread -o $(NAME)

clean:
	@rm -f $(SOURCE_OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


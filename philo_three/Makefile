NAME = philo_three

CC = clang

CFLAGS = -Wall -Wextra -Werror

HEADER = philo_three.h

SRC = philo_three \
	tools \

FIL = $(addsuffix .c, $(addprefix files/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re norm

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: re
	./$(NAME) 2 10000 2000 3000

best: re
	./$(NAME) 2 10000 2000 3000 3

norm:
	norminette $(FIL) files/$(HEADER)

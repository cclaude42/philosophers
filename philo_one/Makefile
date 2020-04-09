NAME = philo_one

CC = clang

CFLAGS = -Wall -Wextra -Werror

THREADS = -lpthread

HEADER = philo_one.h

SRC = philo_one \
	message \
	tools \

FIL = $(addsuffix .c, $(addprefix files/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re norm

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(CC) $(CFLAGS) $(THREADS) -o $(NAME) $(OBJ)
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

norm:
	norminette $(FIL) files/$(HEADER)

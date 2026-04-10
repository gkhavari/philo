NAME    = philo

SRCS    =	main.c \
			input_check.c \
			init.c \
			simulation.c \
			utils.c \
			utils_input_check.c

OBJS    = $(SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "✅ $(NAME) built!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "✅ Created $@"

clean:
	@rm -f $(OBJS)
	@echo "🧹 Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Cleaned executable"

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
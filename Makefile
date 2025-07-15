CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline -lhistory

# Source files
SRCS = \
	builtin_1.c \
	builtin_2.c \
	execute_path.c \
	execute.c \
	minishell_main.c \
	utils_1.c \
	utils_2.c \
	utils_split.c \
	env_utils_1.c \
	export_utils_1.c \
	export_utils_2.c \
	cd_utils_1.c \
	unset_utils_1.c \
	pipeline.c \
	pipeline_utils_1.c \
	$(LIBS) \

# Object files
OBJS = $(SRCS:.c=.o)

# Header
HEADERS = minishell.h

# Output binary
NAME = minishell

# Default rule
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -Iinclude
LIBS = -lreadline -lhistory

SRCS = source/main.c \
		source/main_util.c \
		source/builtin/cd_1.c \
		source/builtin/cd_2.c \
		source/builtin/echo_1.c \
		source/builtin/env_1.c \
		source/builtin/exit_1.c \
		source/builtin/export_1.c \
		source/builtin/export_2.c \
		source/builtin/export_3.c \
		source/builtin/pwd_1.c \
		source/builtin/unset_1.c \
		source/execute/execute_1.c \
		source/execute/execute_2.c \
		source/execute/execute_3.c \
		source/execute/execute_4.c \
		source/execute/execute_5.c \
		source/expand/expand_1.c \
		source/expand/expand_2.c \
		source/free/free_1.c \
		source/free/free_2.c \
		source/input/input_1.c \
		source/lexer/lexer_1.c \
		source/lexer/lexer_2.c \
		source/lexer/lexer_3.c \
		source/parser/parser_1.c \
		source/parser/parser_2.c \
		source/parser/parser_3.c \
		source/parser/parser_4.c \
		source/signal/signal_1.c \
		source/util/ft_atoi.c \
		source/util/ft_bzero.c \
		source/util/ft_calloc.c \
		source/util/ft_isalnum.c \
		source/util/ft_isalpha.c \
		source/util/ft_isnumeric.c \
		source/util/ft_itoa.c \
		source/util/ft_split.c \
		source/util/ft_strchr.c \
		source/util/ft_strcmp.c \
		source/util/ft_strdup.c \
		source/util/ft_strjoin.c \
		source/util/ft_strlen.c \
		source/util/ft_strncmp.c \
		source/util/ft_strndup.c \
		source/util/ft_substr.c
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


leaks: $(NAME) 
	@valgrind --leak-check=full							\
			  --suppressions=readline.supp				\
			  --show-leak-kinds=all 					\
			  --track-origins=yes						\
			  --track-fds=yes							\
			  --verbose									\
			  ./$(NAME)


.PHONY: all clean fclean re

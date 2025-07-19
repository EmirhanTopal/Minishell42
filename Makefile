NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iinclude
LIBS = -lreadline -lhistory

SRCS = src/main.c \
		src/builtin/cd.c \
		src/builtin/echo.c \
		src/builtin/env.c \
		src/builtin/exit.c \
		src/builtin/export.c \
		src/builtin/pwd.c \
		src/builtin/unset.c \
		src/builtin_util/cd_utils_1.c \
		src/builtin_util/echo_utils_1.c \
		src/builtin_util/env_utils_1.c \
		src/builtin_util/export_utils_1.c \
		src/builtin_util/export_utils_2.c \
		src/builtin_util/unset_utils_1.c \
		src/execute/execute_path.c \
		src/execute/execute.c \
		src/free/free.c \
		src/lexer/lexer_1.c \
		src/lexer/lexer_2.c \
		src/lexer/lexer_3.c \
		src/parser/parser_1.c \
		src/parser/parser_2.c \
		src/parser/parser_3.c \
		src/parser/parser_4.c \
		src/pipeline/pipeline_utils_1.c \
		src/pipeline/pipeline.c \
		src/signal/signals_1.c \
		src/util/ft_atoi.c \
		src/util/ft_bzero.c \
		src/util/ft_calloc.c \
		src/util/ft_isalnum.c \
		src/util/ft_isalpha.c \
		src/util/ft_isnumeric.c \
		src/util/ft_itoa.c \
		src/util/ft_split.c \
		src/util/ft_strchr.c \
		src/util/ft_strcmp.c \
		src/util/ft_strdup.c \
		src/util/ft_strjoin.c \
		src/util/ft_strlen.c \
		src/util/ft_strncmp.c \
		src/util/ft_strndup.c \
		src/util/ft_substr.c
		
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

.PHONY: all clean fclean re

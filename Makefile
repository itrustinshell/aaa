NAME = minishell

CC = gcc

#CFLAGS = -Wall -Wextra -Werror

SRC =   tokenizer/fill_tokenmatrix.c tokenizer/get_tokens_number.c tokenizer/tokenizer.c\
		builtins/ft_export.c builtins/ft_env.c builtins/ft_env_lists.c builtins/ft_cd.c builtins/ft_echo.c builtins/ft_exit.c builtins/ft_pwd.c \
		parsing.c\
		executor/executor.c executor/heredoc_utils.c executor/redirutils.c executor/redirops.c executor/pipeutils_p1.c executor/pipeutils_p2.c\
		test/pipe_test.c test/printmatrix.c\
		utils/ft_split.c utils/init.c utils/free.c utils/list_utils.c utils/cmd_utils.c utils/general_utils.c\
		main.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

# Clean object files and MiniLibX
clean:
	rm -f $(OBJ)

# Clean everything, including the final executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Build with optimizations (use this for release, removes AddressSanitizer)
release: CFLAGS := -Wall -Wextra -Werror
release: fclean $(NAME)

all: $(NAME)


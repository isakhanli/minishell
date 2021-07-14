CC = gcc -Wall -Wextra -Werror -g


SRCS =	minishell.c\
		./parsing/main_parser.c\
		./parsing/get_command.c\
		./parsing/get_index.c\
		./parsing/utils.c\
		./parsing/parse_commands.c\
		./parsing/parse_redir.c\
		./parsing/dollar.c\
		./parsing/quotes.c\
		./exec/handle_exec.c\
		./exec/add_bin.c\
		./libft/ft_substr.c\
		./libft/ft_split.c\
        ./libft/ft_strjoin.c\
        ./libft/ft_strnstr.c\
		./libft/ft_strchr.c\
        ./libft/ft_strdup.c\
        ./libft/ft_strlen.c\
        ./libft/ft_strncmp.c\
        ./libft/ft_putstr_fd.c\
        ./libft/ft_putchar_fd.c\
        ./libft/ft_lstadd_back.c\
        ./libft/ft_lstclear.c\
        ./libft/ft_lstdelone.c\
        ./libft/ft_lstlast.c\
        ./libft/ft_lstnew.c\
        ./libft/ft_lstsize.c\
        ./libft/ft_isdigit.c\
        ./libft/ft_isalnum.c

OBJ = $(SRCS:.c=.o)

INCLUDES = ./minishell.h

.c.o:
	$(CC) -c $< -o $@

all: $(OBJ)
	$(CC) $(OBJ) -lreadline  -L /Users/dchin/.brew/Cellar/readline/8.1/lib -I/Users/dchin/.brew/Cellar/readline/8.1/include -o minishell


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ./minishell

re: fclean all


NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g

SRC =	minishell.c \
		signals.c \
		parsing/main_parser.c \
		parsing/get_cmd_n_rdr.c \
		parsing/get_index.c \
		parsing/utils.c \
		parsing/parse_commands.c \
		parsing/parse_redir.c \
		parsing/dollar.c \
		parsing/quotes.c \
		parsing/preparser.c \
		exec/handle_exec2.c \
		exec/add_bin.c \
		exec/builtin_exec.c\
		exec/builtin_func1.c\
		exec/builtin_func2.c\
		exec/builtin_func3.c\
		free_minishell.c\

OBJ = $(SRC:.c=.o)

LIBFT = ./libft


LDFLAGS = /Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS = /Users/$(USER)/.brew/opt/readline/include

CC = gcc
RM = rm -rf

%.o:	%.c
	$(CC) $(CFLAGS) -I$(LIBFT) -I$(CPPFLAGS) -I. -c $< -o $@

all : $(NAME)
	@echo $(NAME) compiled succesfully

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT)
	$(CC) -L$(LDFLAGS) -lreadline -L$(LIBFT) -lft -o  $(NAME) $(OBJ)

clean :
	$(RM) $(OBJ) 
	
fclean : clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) clean
	$(RM) libft/libft.a

re:	fclean all

.PHONY: all clean fclean re

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

SRC =	minishell.c \
		parsing/main_parser.c \
		parsing/get_command.c \
		parsing/get_index.c \
		parsing/utils.c \
		parsing/parse_commands.c \
		parsing/parse_redir.c \
		parsing/dollar.c \
		parsing/quotes.c \
		exec/handle_exec.c \
		exec/add_bin.c
		 
OBJ = $(SRC:.c=.o)

LIBFT = ./libft

LDFLAGS = /Users/jrhyhorn/.brew/opt/readline/lib
CPPFLAGS = /Users/jrhyhorn/.brew/opt/readline/include

CC = gcc
RM = rm -rf

%.o:	%.c
	$(CC) $(CFLAGS) -I$(LIBFT) -I$(CPPFLAGS) -I. -c $< -o $@ 

all : $(NAME)
	@echo $(NAME) comliled succesfully

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT)
	$(CC) -L$(LDFLAGS) -lreadline -L$(LIBFT) -lft -o $(NAME) $(OBJ)

clean :
	$(RM) $(OBJ) 
	
fclean : clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) clean
	$(RM) libft/libft.a

re:	fclean all

.PHONY: all clean fclean re
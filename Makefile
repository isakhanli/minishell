NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g

SRC =	minishell.c \
		signals.c \
		parsing/main_parser.c \
		parsing/parser_utils1.c \
		parsing/parser_utils2.c \
		parsing/parser_utils3.c \
		parsing/parser_utils4.c \
		parsing/parse_commands.c \
		parsing/parse_redir.c \
		parsing/handle_dollars.c \
		parsing/handle_quotes.c \
		parsing/preparser.c \
		parsing/handle_heredoc.c \
		exec/handle_exec.c \
		exec/exec_utils.c \
		exec/add_bin.c \
		exec/builtin_exec.c\
		exec/builtin_func_other.c\
		exec/builtin_func_cd.c\
		exec/builtin_func_export.c\
		exec/builtin_func_unset.c\
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

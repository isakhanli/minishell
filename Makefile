NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g

SRC =	minishell.c \
		src/free_minishell.c \
		src/signals.c \
		parsing/main_parser.c \
		parsing/parser_utils1.c \
		parsing/parser_utils2.c \
		parsing/parser_utils3.c \
		parsing/parser_utils4.c \
		parsing/parser_utils5.c \
		parsing/parse_commands.c \
		parsing/parse_redir.c \
		parsing/handle_dollars.c \
		parsing/handle_quotes.c \
		parsing/preparser.c \
		parsing/handle_heredoc.c \
		exec/handle_exec.c \
		exec/exec_utils.c \
		exec/add_bin.c \
		exec/builtin_exec.c \
		exec/builtin_func_addon.c \
		exec/builtin_func_addon2.c \
		exec/builtin_func_other.c \
		exec/builtin_func_cd.c \
		exec/builtin_func_export2.c \
		exec/builtin_func_export.c \
		exec/builtin_func_unset.c

OBJ = $(SRC:.c=.o)

LDFT = ./libft
CPPFT = ft


LDFLAGS = /Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS = /Users/$(USER)/.brew/opt/readline/include

CC = gcc
RM = rm -rf

%.o:	%.c
	$(CC) $(CFLAGS) -I$(LDFT) -I$(CPPFLAGS) -I. -I./include -c $< -o $@

all : $(NAME)
	@echo $(NAME) compiled succesfully

$(NAME): $(OBJ)
	$(MAKE) -C $(LDFT)
	$(CC) -L$(LDFLAGS) -lreadline -L$(LDFT) -l$(CPPFT) -o  $(NAME) $(OBJ)

clean :
	$(RM) $(OBJ)
	$(MAKE) -C $(LDFT) clean
	
fclean : clean
	$(RM) $(NAME)
	$(MAKE) -C $(LDFT) clean
	$(RM) libft/libft.a

re:	fclean all

.PHONY: all clean fclean re

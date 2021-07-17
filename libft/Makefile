# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile1                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrhyhorn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 21:51:27 by jrhyhorn          #+#    #+#              #
#    Updated: 2020/11/26 20:06:34 by jrhyhorn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HNAME = libft.h

SRC = ft_bzero.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isalpha.c \
	ft_calloc.c ft_lstadd_front.c ft_isprint.c ft_lstnew.c ft_lstlast.c \
	ft_memchr.c ft_lstsize.c ft_putchar_fd.c ft_atoi.c ft_memcmp.c \
	ft_putendl_fd.c ft_putstr_fd.c ft_memccpy.c ft_memset.c ft_memmove.c \
	ft_strlcpy.c ft_strdup.c ft_strlcat.c ft_putnbr_fd.c ft_tolower.c \
	ft_strmapi.c ft_strlen.c ft_strjoin.c ft_toupper.c ft_strrchr.c \
	ft_substr.c  ft_strtrim.c ft_itoa.c ft_memcpy.c ft_strchr.c	\
	ft_strnstr.c ft_split.c ft_strncmp.c ft_lstadd_back.c ft_lstclear.c \
	ft_lstdelone.c

BSRC = $(wildcard ft_lst*.c)

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LIBCOMPILE = gcc $(CFLAGS) -c

LIBCREATE = ar rc $(NAME)

LIBADDINDEX = ranlib $(NAME)

REMOVE = rm -f

all: $(NAME)

$(NAME):	$(OBJ)
	$(LIBCREATE) $(OBJ)
	$(LIBADDINDEX)

%.o:	%.c	$(HNAME)
	@$(LIBCOMPILE) $< -o $@ -I.

bonus:	$(BOBJ)
	@$(LIBCREATE) $(BOBJ)
	@$(LIBADDINDEX)

clean:
	$(REMOVE) $(OBJ) $(BOBJ)

fclean:	clean
	@$(REMOVE) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#   By: ihodge <ihodge@student.42.us.org>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/10 20:17:09 by ihodge            #+#    #+#              #
#    Updated: 2017/11/02 19:00:47 by ihodge           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = filler
SRCS =	main.c \
		save_board_and_piece.c \
		parse.c \
		add_piece.c \
		ncurs_option.c \
		calc_and_print.c
FILES = $(addprefix src/, $(SRCS))
OBJFILES = ${SRCS:.c=.o}
LIB = libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJFILES) $(LIB)
	gcc -Wall -Wextra -Werror $(OBJFILES) $(LIB) -o $@ -lncurses

$(LIB): force
	make -C libft

%.o: src/%.c
	gcc -Wall -Wextra -Werror -c $< -o $@

force:
	@true

clean:
	rm -f $(OBJFILES)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make clean -C libft

re: fclean all

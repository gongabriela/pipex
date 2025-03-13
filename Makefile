# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 11:25:28 by ggoncalv          #+#    #+#              #
#    Updated: 2025/03/13 11:26:46 by ggoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = pipex.c pipex_utils.c
OBJ = $(SRC:.c=.o)

LIBFT = ./Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./Libft
	$(CC) $(CFLAGS) -g $(OBJ) $(LIBFT) -o $(NAME)

debug:
	make -C ./Libft
	cc -g pipex.c pipex_utils.c ./Libft/libft.a -o pipex

clean:
	make -C ./Libft fclean
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

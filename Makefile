# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 11:25:28 by ggoncalv          #+#    #+#              #
#    Updated: 2025/03/27 14:42:14 by ggoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = pipex.c pipex_utils.c tests.c ft_error_free.c
OBJ = $(SRC:.c=.o)

LIBFT = ./Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./Libft
	$(CC) $(CFLAGS) -g $(OBJ) $(LIBFT) -o $(NAME)

debug:
	make -C ./Libft
	cc -g pipex.c pipex_utils.c tests.c ft_error_free.c ./Libft/libft.a -o pipex

clean:
	make -C ./Libft fclean
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

################################TESTING###########################################

test: $(NAME)
	@echo "######################TESTING THE FILES######################"
	@echo " "
	@echo "NON EXISTING FILE"
	@echo "--------------------------------------------------------------"
	@echo "SHELL:"
	@< wrongfile cat || true
	@echo " "
	@echo "PIPEX & VALGRIND:"
	@valgrind --leak-check=full --quiet ./pipex wrongfile "cat" "wc -l" outfile

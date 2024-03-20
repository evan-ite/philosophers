# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:07:09 by evan-ite          #+#    #+#              #
#    Updated: 2024/03/20 11:35:29 by evan-ite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BNS = philo_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
POSIX = -pthread

SRC = src/main.c src/error.c src/init.c src/philo.c src/libft_utils.c \
	src/utils.c src/threads.c src/libft_utils2.c
BNS = bonus/main.c bonus/error.c bonus/libft_utils.c bonus/libft_utils2.c \
	bonus/init.c bonus/philo.c bonus/processes.c bonus/utils.c

OBJ := $(SRC:.c=.o)
BOBJ := $(BNS:.c=.o)

all: $(NAME)

$(NAME): fclean $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(POSIX)

bonus: fclean $(BOBJ)
	$(CC) $(CFLAGS) -o $(NAME_BNS) $(BOBJ) $(POSIX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(BOBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BNS)

re: fclean all

.PHONY: all clean fclean re

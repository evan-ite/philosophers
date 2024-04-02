# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:07:09 by evan-ite          #+#    #+#              #
#    Updated: 2024/04/02 15:02:23 by evan-ite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
POSIX = -pthread -fsanitize=thread -lpthread

BNS = bonus/main.c bonus/error.c bonus/libft_utils.c bonus/libft_utils2.c \
	bonus/init.c bonus/philo.c bonus/utils.c bonus/children.c

BOBJ := $(BNS:.c=.o)

all: $(NAME)

$(NAME): $(BOBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(BOBJ) $(POSIX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

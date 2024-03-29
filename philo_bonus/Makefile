# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:07:09 by evan-ite          #+#    #+#              #
#    Updated: 2024/03/29 17:37:37 by evan-ite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BNS = philo_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
POSIX = -pthread

BNS = bonus/main.c bonus/error.c bonus/libft_utils.c bonus/libft_utils2.c \
	bonus/init.c bonus/philo.c bonus/utils.c bonus/children.c

BOBJ := $(BNS:.c=.o)

all: $(NAME)

bonus: $(BOBJ)
	$(CC) $(CFLAGS) -o $(NAME_BNS) $(BOBJ) $(POSIX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BOBJ)

fclean: clean
	rm -f $(NAME_BNS)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elkan <elkan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 11:49:33 by elkan             #+#    #+#              #
#    Updated: 2026/02/11 22:26:39 by elkan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = check_end.c eating.c ft_atoll.c main.c philo_acts.c print_log.c \
setup.c shutdown.c wait_till.c

OBJECTS = $(SOURCES:%.c=%.o)

NAME = philo

CFLAGS = -Wall -Werror -Wextra -I. -g -pthread

all: $(NAME)

$(NAME): $(OBJECTS) philo.h
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

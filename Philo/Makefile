# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maelle <maelle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 16:11:18 by mberthet          #+#    #+#              #
#    Updated: 2022/02/08 10:06:49 by maelle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

MAIN = srcs/main.c \
		srcs/routine.c \
		srcs/routine_utils.c \
		srcs/basics_utils.c \
		srcs/init.c \
		srcs/time.c \
		srcs/process.c \
		srcs/check.c
		
SOURCES = $(MAIN)

OBJECTS = $(SOURCES:.c=.o)

HEADER = philo.h

all : $(NAME)

$(NAME): $(OBJECTS)
			@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	/bin/rm -f $(OBJECTS) all
	
fclean: clean
	/bin/rm -f $(NAME) all
	
re: fclean all

.PHONY: clean fclean re all

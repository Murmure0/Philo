# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 16:11:18 by mberthet          #+#    #+#              #
#    Updated: 2022/03/04 16:28:57 by mberthet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread
# CFLAGS +=  -fsanitize=thread -g3

MAIN = srcs/main.c \
		srcs/routine.c \
		srcs/routine_utils.c \
		srcs/routine_utils_death.c \
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

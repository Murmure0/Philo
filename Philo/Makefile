# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 16:11:18 by mberthet          #+#    #+#              #
#    Updated: 2022/01/07 16:13:42 by mberthet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MAIN = main.c \
		

SOURCES = $(MAIN)

OBJECTS = $(SOURCES:.c=.o)

HEADER = philo.h

all : $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
			@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	/bin/rm -f $(OBJECTS) all
	
fclean: clean
	/bin/rm -f $(NAME) all
	
re: fclean all

.PHONY: clean fclean re all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 15:30:41 by jmaalouf          #+#    #+#              #
#    Updated: 2022/11/30 17:04:42 by jmaalouf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c init_data.c philo_routine.c philo_routine2.c \
	philosophize.c grim_reaper.c utils.c utils2.c
OBJ = $(addprefix obj/,$(SRC:.c=.o))
CC = cc -pthread -g
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

obj/%.o: %.c | obj
	$(CC) $(FLAGS) -c $< -o $@

obj:
	mkdir obj

clean:
	rm -rf obj

fclean: clean
	rm -r $(NAME)

re: fclean all

.PHONY: all clean fclean re
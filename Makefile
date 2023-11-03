# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 13:01:34 by saazcon-          #+#    #+#              #
#    Updated: 2023/11/03 13:49:52 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRCS	= aristoteles.c philo.c platon.c socrates.c marx.c
OBJS	= ${SRCS:.c=.o}
CC		= gcc -pthread
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=thread 
RM		= rm -f

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
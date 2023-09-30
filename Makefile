# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 13:01:34 by saazcon-          #+#    #+#              #
#    Updated: 2023/09/30 05:36:32 by saazcon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRCS	= philo.c utils.c data.c
OBJS	= ${SRCS:.c=.o}
CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror -g3 -fsanitize=address
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
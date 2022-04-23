FILES = activities.c ft_atoi.c main2.c parsing.c police2.c time.c utils.c

OBJS = ${FILES:.c=.o}

NAME = philo_bonus

FLAGS = -Wall -Wextra -Werror -g

%.o:	%.c
	gcc -c ${FLAGS} -o $@ $<

all: ${NAME}

${NAME}: ${OBJS}
	gcc -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY:	all clean fclean re

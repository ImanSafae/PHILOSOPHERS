FILES = activities.c free.c ft_atoi.c main.c parsing.c philo_utils.c routines.c time.c

OBJS = ${FILES:.c=.o}

NAME = philo

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

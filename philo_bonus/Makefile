NAME = philo_bonus

SRC = ft_output.c\
	  ft_utils.c\
	  p_data_init.c\
	  p_dinner.c\
	  philo_bonus.c\
	  wraps.c

OBJ = ${SRC:.c=.o}

DEPS = philo_bonus.h

CC = cc
CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${DEPS} ${NAME}

${NAME}: ${OBJ}
	${CC} ${SRC} -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

NAME = philo_bonus

SRC = monitoring.c\
	  data_init.c\
	  philo_bonus.c\
	  p_dinner.c\
	  parse_input.c\
	  ft_utils.c\
	  ft_output.c

OBJ = ${SRC:.c=.o}

DEPS = philo_bonus.h

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

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

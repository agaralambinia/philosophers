NAME = philo

SRC = ft_output.c\
	  ft_utils.c\
	  p_begin_dinner.c\
	  p_data_init.c\
	  p_parse_input.c\
	  philo.c\
	  wpaps_dataset.c\
	  wraps_thread.c\
	  ft_death.c\
	  ft_funcs.c

OBJ = ${SRC:.c=.o}

DEPS = philo.h

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

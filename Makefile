NAME = philosophers

SRC = srcs/ft_output.c\
	  srcs/ft_utils.c\
	  srcs/p_begin_dinner.c\
	  srcs/p_data_init.c\
	  srcs/p_parse_input.c\
	  srcs/philosophers.c\
	  srcs/wpaps_dataset.c\
	  srcs/wraps_thread.c\
	  srcs/ft_death.c\
	  srcs/ft_funcs.c

OBJ = ${SRC:.c=.o}

DEPS = incs/philosophers.h

CC = cc
CFLAGS = -Wall -Wextra -Werror

$(OBJDIR)/%.o: %.c
	${CC} -fsanitize=address ${CFLAGS} -c -o $@

all: ${DEPS} ${NAME}

${NAME}: ${OBJ}
	${CC} -fsanitize=address ${SRC} -o $@ #TODO

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

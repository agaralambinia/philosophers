#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef enum	e_code
{
	OPEN,
	CLOSE,
	POST,
	WAIT,
	UNLINK,
}	t_code;

typedef struct s_man
{
	long			man_cnt;
	long			fork_cnt;
	long			eat_tm;
	long			die_tm;
	long			sleep_tm;
	long			meals_cnt;
	long			eaten_meals_cnt;
	bool			eat_flg;
	long			*pid;
	sem_t			*out;
	sem_t			*fork;
	long long int	start_tm;
	long			index;
	long long int	last_dinner_tm;
	pthread_t		monitor;
}	t_man;

void		ft_exit_error(char *error);
char		*incorrect_input_msg(void);
t_man		*man_init(int argc, char **argv);
t_man 		*data_init(int argc, char **argv);
void		*ft_malloc(size_t b);
long		ft_atol(const char *s);

#endif

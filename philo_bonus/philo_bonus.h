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
# include <errno.h>

# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define PINK	"\033[1;35m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"

typedef enum	e_time
{
	SEC,
	MSEC,
	USEC,
}	t_time;

typedef enum	e_code
{
	CREATE,
	DETACH,
	JOIN,
}	t_code;

typedef enum	e_progress
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIE,
}	t_progress;

typedef struct s_man
{
	long			man_cnt;
	long			fork_cnt;
	long			eat_tm;
	long			die_tm;
	long			sleep_tm;
	long			meals_cnt;
	long			eaten_meals_cnt;
	bool			finish_flg;
	bool			die_flg;
	long			*pid;
	sem_t			*out;
	sem_t			*fork;
	long			start_tm;
	long			man_id;
	long			last_dinner_tm;
	pthread_t		monitor;
}	t_man;

void		ft_exit_error(char *error);
char		*incorrect_input_msg(void);
t_man		*man_init(char **argv);
t_man 		*data_init(char **argv);
void		*ft_malloc(size_t b);
long		ft_atol(const char *s);
void		progress_log(t_progress event, t_man *man);
void		begin_dinner(t_man *man);
void 		ft_usleep(long usec, t_man *man);
void		*monitor(void *data);
void		clean(t_man **man);
long		ft_get_time(t_time code);

#endif

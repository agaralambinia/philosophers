#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define PINK	"\033[1;35m"
# define GREEN	"\03S3[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"

# define DEBUG_MODE	0 //TODO DELETE

typedef enum	e_code
{
	INIT,
	LOCK,
	UNLOCK,
	CREATE,
	DESTROY,
	DETACH,
	JOIN,
}	t_code;

typedef enum	e_time
{
	SEC,
	MSEC,
	USEC,
}	t_time;

typedef enum	e_progress
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIE,
}	t_progress;

typedef struct s_table t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	long			fork_id;
}	t_fork;

typedef struct s_man
{
	long			man_id;
	long			meals_cnt;
	bool			eat_flg;
	long			last_dinner_tm;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_table			*table;
	pthread_mutex_t	man_mutex;
}	t_man;

typedef struct s_table
{
	long			man_cnt;
	long			die_tm;
	long			eat_tm;
	long			sleep_tm;
	long			meals_cnt;
	long			start_tm;
	bool			end_flg;
	t_fork			*forks;
	t_man			*men;
	bool			men_ready;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_lock;
	pthread_t		monitor;
	long			thread_cnt;
}	t_table;

void		ft_exit_error(char *error);
char		*incorrect_input_msg(void);
void		parse_input(t_table *table, char **argv);
const char	*validate_input(const char *s);
void		data_init(t_table *table);
void		*ft_malloc(size_t b);
void		ft_mutex(pthread_mutex_t *m, t_code code);
void		ft_mutex_error(int status, t_code code);
void		ft_thread(pthread_t *t, void *(*f)(void *), void *val, t_code code);
void		ft_thread_error(int status, t_code code);
void		man_init(t_table *table);
void		place_forks(t_man *man, t_fork *forks, int seat);
void		*dinner(void *data);
void		ft_write_bool(pthread_mutex_t *mutex, bool *dst, bool v);
bool		ft_read_bool(pthread_mutex_t *mutex, bool *dst);
void		ft_write_long(pthread_mutex_t *mutex, long *dst, long v);
long		ft_read_long(pthread_mutex_t *mutex, long *dst);
bool		dinner_finished(t_table *table);
void		wait_beginning(t_table *table);
long		ft_get_time(t_time code);
void		ft_usleep(long usec, t_table *table);
void		progress_log(t_progress event, t_man *man, bool debug); //TODO DELETE DEBUG
void 		eat(t_man *man);
void		think(t_man *man);
long		ft_atol(const char *s);
void		begin_dinner(t_table *table);
void		*monitor_death(void *data);
bool		everyman_threads(pthread_mutex_t *mutex, long *threads, long man);
bool		dead_man(t_man *man);
#endif

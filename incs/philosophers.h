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
}	t_table;

void		ft_exit_error(char *error);
char		*incorrect_input_msg(void);
void		parse_input(t_table *table, char **argv);
const char	validate_input(const char *s);
void		data_init(t_table *table);
void		*ft_malloc(size_t b);
void		*ft_mutex(pthread_mutex_t *m, t_code code);
void		*ft_mutex_error(int status, t_code code);
void		*ft_thread(pthread_t *t, void *(*f)(void *), void *val, t_code code);
void		*ft_thread_error(int status, t_code code);
void		man_init(t_table *table);
void		place_forks(t_man *man, t_fork *forks, int seat);
void		*dinner(void *data);
void		ft_write_bool(pthread_mutex_t *mutex, bool *dst, bool v);
void		ft_read_bool(pthread_mutex_t *mutex, bool *dst);
void		ft_write_long(pthread_mutex_t *mutex, long *dst, long v);
void		ft_read_long(pthread_mutex_t *mutex, long *dst);
bool		dinner_finisher(t_table *table);
void		wait_beginning(t_table *table);
#endif

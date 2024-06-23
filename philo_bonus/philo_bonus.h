/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:55:34 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:55:36 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define R	"\033[0m"
# define RED	"\033[1;31m"
# define PINK	"\033[1;35m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"

# define SEAT "/eat"
# define SLASTEAT "/lasteat"
# define SFORKS "/forks"
# define SWRITE "/write"
# define SDIE "/die"

typedef enum e_progress
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIE,
}	t_progress;

typedef enum e_time
{
	SEC,
	MSEC,
	USEC,
}	t_time;

struct	s_table;

typedef struct s_man
{
	long long		lasteat;
	bool			*dead_flg;
	int				id;
	int				meal_counter;
	pid_t			pid;
	pthread_t		thread;
	pthread_mutex_t	each_eat;
	struct s_table	*table;
}		t_man;

typedef struct s_table
{
	int				man_cnt;
	long			start_tm;
	int				die_tm;
	int				meals_cnt;
	int				eat_tm;
	int				sleep_tm;
	bool			dead_flg;
	t_man			*men;
	sem_t			*forks;
	sem_t			*s_write;
	sem_t			*s_die;
	sem_t			*s_eat;
	sem_t			*s_lasteat;
}		t_table;

void	parse_input(int argc, char *argv[], t_table *table);
long	ft_atol(const char *s);
void	ft_exit_error(char *error);
void	data_init(t_table *table);
void	ft_unlink(t_table *table);
void	begin_dinner(t_table *table);
char	*incorrect_input_msg(void);
long	ft_get_time(t_time code);
void	ft_sleep(long long tm);
void	set_lasteat(t_man *p);
void	*monitor(t_man *man);
void	*ft_malloc(size_t b);
void	progress_log(t_progress event, t_man *man);
int		death_check(t_man *man);

#endif
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

# define R		"\033[0m"
# define RED	"\033[1;31m"
# define P		"\033[1;35m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define B		"\033[1;34m"

# define SLASTEAT "/lasteat"
# define SFORKS "/forks"
# define SWRITE "/write"
# define SDIE "/die"
# define SEAT "/eat"

typedef enum e_progress
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
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
	long			lasteat;
	bool			*dead_flg;
	long			*start_tm;
	int				id;
	int				meal_counter;
	pid_t			pid;
	pthread_t		thread;
	struct s_table	*table;
}		t_man;

typedef struct s_table
{
	int				man_cnt;
	long			die_tm;
	int				meals_cnt;
	long			eat_tm;
	long			start_tm;
	long			sleep_tm;
	bool			dead_flg;
	t_man			*men;
	sem_t			*forks;
	sem_t			*s_write;
	sem_t			*s_die;
	sem_t			*s_lasteat;
	sem_t			*s_eat;
}		t_table;

void	parse_input(int argc, char **argv, t_table *table);
long	ft_atol(const char *s);
void	ft_exit_error(char *error);
void	data_init(t_table *table);
void	ft_unlink(t_table *table);
void	fork_men(t_table *table);
char	*incorrect_input_msg(void);
long	ft_time(void);
void	ft_sleep(long tm);
void	set_lasteat(t_man *man);
void	*monitor(t_man *man);
void	progress_log(t_progress event, t_man *man);

#endif
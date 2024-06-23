#include "philo_bonus.h"

void	ft_exit_error(char *error)
{
	printf(RED"%s\n"R, error);
	exit(EXIT_FAILURE);
}

char	*incorrect_input_msg(void)
{
	return ("Incorrect input. Provide\n\
 * number_of_philosophers\n * time_to_die\n\
 * time_to_eat\n * time_to_sleep\n\
 * number_of_tms_each_philosopher_meals_cnt (optional)");
}

void	progress_log(t_progress event, t_man *man)
{
	long	s;

	sem_wait(man->table->s_write);
	s = ft_get_time(USEC) - man->table->start_tm;
	if (!death_check(man))
	{
		if (event == TAKE_FIRST_FORK || event == TAKE_SECOND_FORK)
			printf(PINK"%ld	%d has taken a fork\n"R, s / 1000, man->id + 1);
		else if (event == EAT)
			printf(YELLOW"%ld	%d is eating\n"R, s / 1000, man->id + 1);
		else if (event == SLEEP)
			printf(BLUE"%ld	%d is sleeping\n"R, s / 1000, man->id + 1);
		else if (event == THINK)
			printf(GREEN"%ld	%d is thinking\n"R, s / 1000, man->id + 1);
	}
	else if (event == DIE)
		printf(RED"%ld	%d died\n"R, s / 1000, man->id + 1);
	sem_post(man->table->s_write);
}

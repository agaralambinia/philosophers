#include "philo.h"

void	ft_exit_error(char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}

char	*incorrect_input_msg(void)
{
	return ("Incorrect input. Provide\n\
 * number_of_philosophers\n * time_to_die\n\
 * time_to_eat\n * time_to_sleep\n\
 * number_of_times_each_philosopher_must_eat (optional)");
}

void	progress_log(t_progress event, t_man *man)
{
	long	spent;
	spent = ft_get_time(MSEC) - man->table->start_tm;
	if (man->eat_flg)
		return ;
	ft_mutex(&man->table->write_lock, LOCK);
	if (!dinner_finished(man->table))
	{
		if (event == TAKE_FIRST_FORK || event == TAKE_SECOND_FORK)
			printf("%ld"PINK"	%ld has taken a fork\n"RESET, spent, man->man_id);
		else if (event == EAT)
			printf("%ld"YELLOW"	%ld is eating\n"RESET, spent, man->man_id);
		else if (event == SLEEP)
			printf("%ld"BLUE"	%ld is sleeping\n"RESET, spent, man->man_id);
		else if (event == THINK)
			printf("%ld"GREEN"	%ld is thinking\n"RESET, spent, man->man_id);
	}
	else if (event == DIE)
		printf("%ld"RED"	%ld died\n"RESET, spent, man->man_id);
	ft_mutex(&man->table->write_lock, UNLOCK);
}
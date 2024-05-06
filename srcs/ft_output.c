#include "../incs/philosophers.h"

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
//TODO DELETE
static void	write_status_debug(t_progress status, t_man *philo,
		long elapsed)
{
	if (TAKE_FIRST_FORK == status && !dinner_finished(philo->table))
		printf(GREEN"%6ld"RESET" %ld has taken the 1° fork 🍽"
			"\t\t\tn°"GREEN"[🍴 %ld 🍴]\n"RESET, elapsed, philo->man_id,
			philo->left_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !dinner_finished(philo->table))
		printf(GREEN"%6ld"RESET" %ld has taken the 2° fork 🍽"
			"\t\t\tn°"GREEN"[🍴 %ld 🍴]\n"RESET, elapsed, philo->man_id,
			philo->right_fork->fork_id);
	else if (EAT == status && !dinner_finished(philo->table))
		printf(GREEN"%6ld"RESET" %ld is eating 🍝\n"YELLOW"[🍝 %ld 🍝]\n"RESET, elapsed, philo->man_id, philo->meals_cnt);
	else if (SLEEP == status && !dinner_finished(philo->table))
		printf(GREEN"%6ld"RESET" %ld is sleeping 😴\n", elapsed, philo->man_id);
	else if (THINK == status && !dinner_finished(philo->table))
		printf(GREEN"%6ld"RESET" %ld is thinking 🤔\n", elapsed, philo->man_id);
	else if (DIE == status)
		printf(RED"\t\t💀💀💀 %6ld %ld died   💀💀💀\n"RESET, elapsed, philo->man_id);
}

void	progress_log(t_progress event, t_man *man, bool debug)
{
	long	spent;
	spent = ft_get_time(MSEC) - man->table->start_tm;
	if (man->eat_flg)
		return ;
	ft_mutex(&man->table->write_lock, LOCK);
	if (debug) //TODO
		write_status_debug(event, man, spent);
	else
	{
		if (!dinner_finished(man->table))
		{
			if (event == TAKE_FIRST_FORK || event == TAKE_FIRST_FORK)
				printf("%-10ld" PINK"%ld has taken a fork 🍴\n"RESET, spent, man->man_id);
			else if (event == EAT)
				printf("%-10ld" YELLOW"%ld started eating 🍝\n"RESET, spent, man->man_id);
			else if (event == SLEEP)
				printf("%-10ld" BLUE"%ld started sleaping 💤\n"RESET, spent, man->man_id);
			else if (event == THINK)
				printf("%-10ld" GREEN"%ld started thinking 🤔\n"RESET, spent, man->man_id);
		}
		else if (event == DIE)
			printf("%-10ld" RED"%ld DIED 💀\n"RESET, spent, man->man_id);
	}
	ft_mutex(&man->table->write_lock, UNLOCK);
}
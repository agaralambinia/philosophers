#include "philo_bonus.h"

int	death_check(t_man *man)
{
	int	i;

	sem_wait(man->table->s_die);
	i = *man->dead_flg;
	sem_post(man->table->s_die);
	return (i);
}

void	*ft_dinner(t_man *man)
{
	pthread_create(&man->thread, NULL, (void *)monitor, man);
	set_lasteat(man);
	man->table->start_tm = ft_get_time(USEC);
	while (1)
	{
		sem_wait(man->table->forks);
		progress_log(TAKE_FIRST_FORK, man);
		sem_wait(man->table->forks);
		progress_log(TAKE_SECOND_FORK, man);
		progress_log(EAT, man);
		ft_sleep(man->table->eat_tm);
		sem_post(man->table->forks);
		sem_post(man->table->forks);
		sem_wait(man->table->s_eat);
		man->meal_counter++;
		sem_post(man->table->s_eat);
		progress_log(SLEEP, man);
		set_lasteat(man);
		ft_sleep(man->table->sleep_tm);
		if (!man->table->dead_flg)
			progress_log(THINK, man);
	}
	pthread_join(man->thread, NULL);
	exit (0);
}

void	begin_dinner(t_table *table)
{
	int	i;
	int	status;

	i = -1;
	while (++i < table->man_cnt)
	{
		table->men[i].pid = fork();
		if (table->men[i].pid == 0)
			ft_dinner(&table->men[i]);
	}
	i = -1;
	while (++i <= table->man_cnt)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) > 0)
		{
			i = -1;
			while (++i < table->man_cnt)
				kill(table->men[i].pid, SIGKILL);
			break ;
		}
	}
	ft_unlink(table);
	free(table->men);
}

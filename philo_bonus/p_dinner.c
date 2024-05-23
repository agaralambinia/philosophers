#include "philo_bonus.h"

void	begin_dinner(t_man *man)
{
	printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
	if (pthread_create(&man->monitor, \
			NULL, &monitor, man))
		ft_exit_error("Failed to create thread");
	printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
	if (man->man_id % 2 == 1)
		usleep(500);
	printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
	while (1)
	{
		progress_log(THINK, man);
		sem_wait(man->fork);
		progress_log(TAKE_FIRST_FORK, man);
		sem_wait(man->fork);
		progress_log(TAKE_FIRST_FORK, man);
		progress_log(EAT, man);
		ft_usleep(man->eat_tm * 1000, man);
		printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
		man->last_dinner_tm = ft_get_time(MSEC);
		sem_post(man->fork);
		sem_post(man->fork);
		man->eaten_meals_cnt += 1;
		progress_log(SLEEP, man);
		ft_usleep(man->sleep_tm * 1000, man);
	}
	if (pthread_join(man->monitor, NULL))
		ft_exit_error("Failed to join thread");
}

void	clean(t_man **man)
{
	t_man	*temp;
	int		i;
	int		status;

	temp = *man;
	i = 0;
	while (i < temp->man_cnt)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < temp->man_cnt)
				kill(temp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(temp->out);
	sem_close(temp->fork);
	sem_unlink("out");
	sem_unlink("fork");
	free(temp->pid);
	free(temp);
}

void	*monitor(void *data)
{
	t_man	*man;

	man = (t_man *)data;
	while (!man->finish_flg)
	{
		usleep(100);
		if (ft_get_time(MSEC) - (man->eat_tm) > man->die_tm)
		{
			man->die_flg = true;
			sem_wait(man->out);
			progress_log(DIE, man);
			man->finish_flg = true;
			break ;
		}
		if (man->meals_cnt != -1 && man->eaten_meals_cnt >= man->meals_cnt)
		{
			man->finish_flg = true;
			break ;
		}
	}
	if (man->die_flg)
		exit (1);
	else
		exit (0);
}
#include "philo_bonus.h"

void	force_think(t_man *man)
{
	long	think_tm;

	think_tm = (man->eat_tm) * 2 - (man->sleep_tm);
	if (think_tm < 0)
		think_tm = 0;
	if (man->man_cnt % 2 == 1)
	{
		if (man->man_id % 2 == 1)
			ft_usleep(think_tm / 2, man);
	}
	else
	{
		if (man->man_id % 2 == 1)
			ft_usleep(man->eat_tm / 2, man);
	}
}

void	begin_dinner(t_man *man)
{
	ft_thread(&man->monitor, NULL, monitor, CREATE);
	force_think(man);
	while (1)
	{
		progress_log(THINK, man);
		sem_wait(man->fork);
		progress_log(TAKE_FIRST_FORK, man);
		sem_wait(man->fork);
		progress_log(TAKE_FIRST_FORK, man);
		progress_log(EAT, man);
		ft_usleep(man->eat_tm, man);
		man->eat_tm = ft_get_time(MSEC);
		sem_post(man->fork);
		sem_post(man->fork);
		man->eaten_meals_cnt += 1;
		progress_log(SLEEP, man);
		ft_usleep(man->sleep_tm, man);
	}
	ft_thread(&man->monitor, NULL, NULL, JOIN);
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
		usleep(60);
		if (ft_get_time(MSEC) - (man->eat_tm * 1000) > man->die_tm)
		{
			man->die_flg = true;
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
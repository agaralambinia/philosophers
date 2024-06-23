#include "philo_bonus.h"

static int	check_die(t_man *man)
{
	sem_wait(man->table->s_lasteat);
	if (ft_get_time(MSEC) - man->lasteat >= man->table->die_tm)
	{
		sem_wait(man->table->s_die);
		man->table->dead_flg = true;
		sem_post(man->table->s_die);
		progress_log(DIE, man);
		sem_post(man->table->s_lasteat);
		exit(1);
	}
	sem_post(man->table->s_lasteat);
	return (0);
}

static int	check_eat(t_man *man)
{
	sem_wait(man->table->s_eat);
	if (man->meal_counter == man->table->meals_cnt)
	{
		sem_wait(man->table->s_die);
		man->table->dead_flg = true;
		sem_post(man->table->s_die);
		sem_post(man->table->s_eat);
		exit (0);
	}
	sem_post(man->table->s_eat);
	return (0);
}

void	set_lasteat(t_man *p)
{
	sem_wait(p->table->s_lasteat);
	p->lasteat = ft_get_time(MSEC);
	sem_post(p->table->s_lasteat);
}

void	*monitor(t_man *man)
{
	while (true)
	{
		if (check_die(man) == 1 || check_eat(man) == 1)
			break ;
	}
	return (NULL);
}

#include "../incs/philosophers.h"

bool	everyman_threads(pthread_mutex_t *mutex, long *threads, long man_cnt)
{
	bool	result;

	result = false;
	ft_mutex(mutex, LOCK);
	if (*threads == man_cnt)
		result == true;
	ft_mutex(mutex, UNLOCK);
	return (result);
}

bool	dead_man(t_man *man)
{
	if (ft_read_bool(&man->man_mutex, &man->eat_flg))
		return (false);
	if (ft_get_time(MSEC) - ft_read_long(&man->man_mutex, \
		&man->last_dinner_tm) > man->table->die_tm / 1000)
		return (true);
	return (false);
}

void	*monitor_death(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!everyman_threads(&table->table_mutex, &table->thread_cnt, table->man_cnt))
		;
	while (!dinner_finished(table))
	{
		i = 0;
		while (i < table->man_cnt && !dinner_finished(table))
		{
			if (dead_man(table->men + i))
			{
				ft_write_bool(&table->table_mutex, &table->end_flg, true);
				progress_log(DIE, table->men + i, DEBUG_MODE);
			}
		i++;
		}
	}
	return (NULL);
}
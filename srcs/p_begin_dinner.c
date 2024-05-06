#include "../incs/philosophers.h"

void 	eat(t_man *man)
{
	ft_mutex(&man->left_fork->fork_mutex, LOCK);
	progress_log(TAKE_FIRST_FORK, man, DEBUG_MODE);
	ft_mutex(&man->right_fork->fork_mutex, LOCK);
	progress_log(TAKE_SECOND_FORK, man, DEBUG_MODE);
	ft_write_long(&man->man_mutex, &man->last_dinner_tm, ft_get_time(MSEC));
	man->meals_cnt++;
	progress_log(EAT, man, DEBUG_MODE);
	ft_usleep(man->table->eat_tm, man->table);
	if (man->table->meals_cnt > 0 && man->meals_cnt == man->table->meals_cnt)
		ft_write_bool(&man->man_mutex, &man->eat_flg, true);
	ft_mutex(&man->left_fork->fork_mutex, UNLOCK);
	ft_mutex(&man->right_fork->fork_mutex, UNLOCK);
}

void 	think(t_man *man)
{
	progress_log(THINK, man, DEBUG_MODE);
}

void *one_man(void *arg)
{

}

void	*dinner(void *data)
{
	t_man *man;

	man = (t_man *)data;
	//printf("DEBUG p_begin_dinner %d\n", __LINE__);
	wait_beginning(man->table);
	ft_write_long(&man->man_mutex, &man->last_dinner_tm, ft_get_time(MSEC));
	ft_write_long(&man->table->table_mutex, &man->table->thread_cnt, \
		man->table->thread_cnt + 1);
	//printf("DEBUG p_begin_dinner %d\n", __LINE__);
	while (!dinner_finished(man->table))
	{
		//printf("DEBUG p_begin_dinner %d\n", __LINE__);
		if (man->eat_flg)
			break ;
		//printf("DEBUG p_begin_dinner %d\n", __LINE__);
		eat(man);
		//printf("DEBUG p_begin_dinner %d\n", __LINE__);
		progress_log(SLEEP, man, DEBUG_MODE);
		//printf("DEBUG p_begin_dinner %d\n", __LINE__);
		ft_usleep(man->table->sleep_tm, man->table);
		//printf("DEBUG p_begin_dinner %d\n", __LINE__);
		think(man);
	}
	return (NULL);
}

void	begin_dinner(t_table *table)
{
	int	i;

	i = 0;

	if (table->man_cnt == 1)
		ft_thread(&table->men[0].thread_id, one_man, &table->men[0], CREATE); //TODO
	else if (table->meals_cnt == 0)
		return ;
	else
	{
		while (i < table->man_cnt)
		{
			//printf("DEBUG p_begin_dinner %d\n", __LINE__);
			ft_thread(&table->men[i].thread_id, dinner, &table->men[i], CREATE);
			i++;
		}
	}
	ft_thread(&table->monitor, monitor_death, table, CREATE);
	//printf("DEBUG p_begin_dinner %d\n", __LINE__);
	table->start_tm = ft_get_time(MSEC);
	//printf("DEBUG p_begin_dinner %d\n", __LINE__);
	ft_write_bool(&table->table_mutex, &table->men_ready, true);
	//printf("DEBUG p_begin_dinner %d\n", __LINE__);
	i = 0;
	//printf("DEBUG p_begin_dinner %d\n", __LINE__);
	while (i < table->man_cnt)
	{
		//printf("DEBUG p_begin_dinner %d\n", __LINE__);
		ft_thread(&table->men[i].thread_id, NULL, NULL, JOIN);
		//printf("DEBUG p_begin_dinner %d\n", __LINE__);
		i++;
	}
	//printf("DEBUG p_begin_dinner %d\n", __LINE__);
}

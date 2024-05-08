#include "../incs/philosophers.h"

void	place_forks(t_man *man, t_fork *forks, int seat)
{
	if (man->man_id % 2 == 0)
	{
		man->right_fork = &forks[seat];
		man->left_fork = &forks[(seat + 1) % (man->table->man_cnt)];
	}
	else
	{
		man->right_fork = &forks[(seat + 1) % (man->table->man_cnt)];
		man->left_fork = &forks[seat];
	}
}

void	man_init(t_table *table)
{
	int	i;
	t_man *man;

	i = -1;
	while (++i < table->man_cnt)
	{
		man = table->men + i;
		man->meals_cnt = 0;
		man->man_id = i + 1;
		man->eat_flg = false;
		man->table = table;
		ft_mutex(&man->man_mutex, INIT);
		place_forks(man, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_flg = false;
	table->men_ready = false;
	table->forks = ft_malloc(sizeof(t_fork) * (table->man_cnt));
	table->men = ft_malloc(sizeof(t_man) * (table->man_cnt));
	table->thread_cnt = 0;
	ft_mutex(&table->table_mutex, INIT);
	ft_mutex(&table->write_lock, INIT);
	while (++i < table->man_cnt)
	{
		ft_mutex(&table->forks[i].fork_mutex, INIT);
		table->forks[i].fork_id = i;
	}
	man_init(table);
}
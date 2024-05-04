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

	i = 0;
	while (i++ < table->man_cnt)
	{
		man = table->men + 1;
		man->meals_cnt = 0;
		man->man_id = i + 1;
		man->eat_flg = false;
		place_forks(man, table->forks, i);
		man->table = table;
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_flg = false;
	table->men_ready = false;
	table->forks = ft_malloc(sizeof(t_fork) * table->man_cnt);
	table->men = ft_malloc(sizeof(t_man) * table->man_cnt);
	ft_mutex(table->table_mutex, INIT);
	while (i++ < table->man_cnt)
	{
		table->forks[i].fork_id = i;
		ft_mutex(table->forks[i].fork_mutex, INIT);
	}
	man_init(table);
}
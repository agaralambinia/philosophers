#include "../incs/philosophers.h"

void	place_forks(t_man *man, t_fork *forks, int seat)
{
	//printf("DEBUG p_data_init %d\n", __LINE__);
	if (man->man_id % 2 == 0)
	{
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man->right_fork = &forks[seat];
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man->left_fork = &forks[(seat + 1) % (man->table->man_cnt)];
		//printf("DEBUG p_data_init %d\n", __LINE__);
	}
	else
	{
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man->right_fork = &forks[(seat + 1) % (man->table->man_cnt)];
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man->left_fork = &forks[seat];
		//printf("DEBUG p_data_init %d\n", __LINE__);
	}
}

void	man_init(t_table *table)
{
	int	i;
	t_man *man;

	i = 0;
	//printf("DEBUG p_data_init %d\n", __LINE__);
	while (i < table->man_cnt)
	{
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man = table->men + 1;
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man->meals_cnt = 0;
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man->man_id = i + 1;
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man->eat_flg = false;
		//printf("DEBUG p_data_init %d\n", __LINE__);
		man->table = table;
		//printf("DEBUG p_data_init %d\n", __LINE__);
		place_forks(man, table->forks, i);
		//printf("DEBUG p_data_init %d\n", __LINE__);
		ft_mutex(&man->man_mutex, INIT);
		//printf("DEBUG p_data_init %d\n", __LINE__);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	//printf("DEBUG p_data_init %d\n", __LINE__);
	table->end_flg = false;
	//printf("DEBUG p_data_init %d\n", __LINE__);
	table->men_ready = false;
	//printf("DEBUG p_data_init %d\n", __LINE__);
	table->forks = ft_malloc(sizeof(t_fork) * (table->man_cnt));
	//printf("DEBUG p_data_init %d\n", __LINE__);
	table->men = ft_malloc(sizeof(t_man) * table->man_cnt);
	//printf("DEBUG p_data_init %d\n", __LINE__);
	table->thread_cnt = 0;
	ft_mutex(&table->table_mutex, INIT);
	//printf("DEBUG p_data_init %d\n", __LINE__);
	ft_mutex(&table->write_lock, INIT);
	//printf("DEBUG p_data_init %d\n", __LINE__);
	while (i < table->man_cnt)
	{
		//printf("DEBUG p_data_init %d\n", __LINE__);
		ft_mutex(&table->forks[i].fork_mutex, INIT);
		//printf("DEBUG p_data_init %d %d\n", __LINE__, i);
		table->forks[i].fork_id = i;
		//printf("DEBUG p_data_init %d\n", __LINE__);
		i++;
	}
	//printf("DEBUG p_data_init %d\n", __LINE__);
	man_init(table);
	//printf("DEBUG p_data_init %d\n", __LINE__);
}
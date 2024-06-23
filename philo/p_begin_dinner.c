/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_begin_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:50:21 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:50:29 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_man *man)
{
	ft_mutex(&man->lf->fork_mutex, LOCK);
	progress_log(TAKE_FIRST_FORK, man);
	ft_mutex(&man->rf->fork_mutex, LOCK);
	progress_log(TAKE_SECOND_FORK, man);
	ft_write_long(&man->man_mutex, &man->last_d_tm, ft_gettm(MSEC));
	progress_log(EAT, man);
	man->meals_cnt++;
	ft_usleep((man->table->eat_tm), man->table);
	if (man->meals_cnt == man->table->meals_cnt)
		ft_write_bool(&man->man_mutex, &man->eat_flg, true);
	ft_mutex(&man->lf->fork_mutex, UNLOCK);
	ft_mutex(&man->rf->fork_mutex, UNLOCK);
}

void	think(t_man *man, bool syncro_flg)
{
	long	think_tm;

	if (!syncro_flg)
		progress_log(THINK, man);
	if (man->table->man_cnt % 2 == 0)
		return ;
	think_tm = (man->table->eat_tm) * 2 - (man->table->sleep_tm);
	if (think_tm < 0)
		think_tm = 0;
	ft_usleep(think_tm / 2, man->table);
}

void	*one_man(void *data)
{
	t_man	*man;

	man = (t_man *)data;
	wait_beginning(man->table);
	ft_write_long(&man->man_mutex, &man->last_d_tm, ft_gettm(MSEC));
	ft_plus_long(&man->table->table_mutex, &man->table->thread_cnt);
	progress_log(TAKE_FIRST_FORK, man);
	while (!dinner_finished(man->table))
		usleep(100);
	return (NULL);
}

void	*dinner(void *data)
{
	t_man	*man;

	man = (t_man *)data;
	wait_beginning(man->table);
	ft_write_long(&man->man_mutex, &man->last_d_tm, ft_gettm(MSEC));
	ft_plus_long(&man->table->table_mutex, &man->table->thread_cnt);
	force_think(man);
	while (!dinner_finished(man->table))
	{
		if (ft_read_bool(&man->man_mutex, &man->eat_flg))
			break ;
		eat(man);
		progress_log(SLEEP, man);
		ft_usleep(man->table->sleep_tm, man->table);
		think(man, false);
	}
	return (NULL);
}

void	begin_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->man_cnt == 1)
		ft_thread(&table->men[0].thread_id, one_man, &table->men[0], CREATE);
	else if (table->meals_cnt == 0)
		return ;
	else
	{
		while (++i < table->man_cnt)
			ft_thread(&table->men[i].thread_id, dinner, &table->men[i], CREATE);
	}
	ft_thread(&table->monitor, monitor_death, table, CREATE);
	table->start_tm = ft_gettm(MSEC);
	ft_write_bool(&table->table_mutex, &table->men_ready, true);
	i = -1;
	while (++i < table->man_cnt)
		ft_thread(&table->men[i].thread_id, NULL, NULL, JOIN);
	ft_write_bool(&table->table_mutex, &table->end_flg, true);
	ft_thread(&table->monitor, NULL, NULL, JOIN);
}

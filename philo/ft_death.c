/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:46:58 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:46:59 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_thread(pthread_mutex_t *mutex, long *threads, long man_cnt)
{
	bool	result;

	result = false;
	ft_mutex(mutex, LOCK);
	if (*threads == man_cnt)
		result = true;
	ft_mutex(mutex, UNLOCK);
	return (result);
}

bool	dead_man(t_man *man)
{
	if (ft_read_bool(&man->man_mutex, &man->eat_flg))
		return (false);
	if (ft_gettm(MSEC) - (ft_read_long(&man->man_mutex, &man->last_d_tm))
		> ((man->table->die_tm) / 1000))
		return (true);
	return (false);
}

bool	dinner_finished(t_table *table)
{
	bool	end_flg;

	end_flg = ft_read_bool(&table->table_mutex, &table->end_flg);
	return (end_flg);
}

void	*monitor_death(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_thread(&table->table_mutex, &table->thread_cnt, table->man_cnt))
		;
	while (!dinner_finished(table))
	{
		i = -1;
		while (++i < table->man_cnt && !dinner_finished(table))
		{
			if (dead_man(table->men + i) == true)
			{
				ft_write_bool(&table->table_mutex, &table->end_flg, true);
				progress_log(DIE, table->men + i);
			}
		}
	}
	return (NULL);
}

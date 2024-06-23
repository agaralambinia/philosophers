/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:47:59 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:48:01 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_gettm(t_time code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_exit_error("Error: gettimeofday function failed.");
	if (code == SEC)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (code == MSEC)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (code == USEC)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		ft_exit_error("Error: gettimeofday mistake");
	return (-1);
}

void	ft_usleep(long usec, t_table *table)
{
	long	asleep;
	long	spent;
	long	left;

	spent = 0;
	asleep = ft_gettm(USEC);
	while (spent < usec)
	{
		if (dinner_finished(table) == true)
			break ;
		spent = ft_gettm(USEC) - asleep;
		left = usec - spent;
		if (left > 1000)
			usleep(left / 2);
		else
		{
			while (ft_gettm(USEC) - asleep < usec)
				;
		}
	}
}

void	wait_beginning(t_table *table)
{
	while (!ft_read_bool(&table->table_mutex, &table->men_ready))
		;
}

void	force_think(t_man *man)
{
	if (man->table->man_cnt % 2 == 1)
	{
		if (man->man_id % 2 == 1)
			think(man, true);
	}
	else
	{
		if (man->man_id % 2 == 0)
			ft_usleep(man->table->eat_tm / 2, man->table);
	}
}

void	clean(t_table *table)
{
	t_man	*man;
	int		i;

	i = -1;
	while (++i < table->man_cnt)
	{
		man = table->men + i;
		ft_mutex(&man->man_mutex, DESTROY);
	}
	ft_mutex(&table->write_lock, DESTROY);
	ft_mutex(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->men);
}

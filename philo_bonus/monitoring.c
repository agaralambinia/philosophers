/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:54:52 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:54:57 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	death_monitor(t_man *man)
{
	sem_wait(man->table->s_lasteat);
	if ((ft_time() - man->lasteat) / 1000 >= man->table->die_tm)
	{
		sem_wait(man->table->s_die);
		man->table->dead_flg = true;
		sem_wait(man->table->s_write);
		progress_log(DIE, man);
		sem_post(man->table->s_die);
		sem_post(man->table->s_lasteat);
		exit(1);
	}
	sem_post(man->table->s_lasteat);
	return (0);
}

static int	fill_monitor(t_man *man)
{
	sem_wait(man->table->s_eat);
	if (man->meal_counter == man->table->meals_cnt)
	{
		sem_wait(man->table->s_die);
		man->table->dead_flg = true;
		sem_post(man->table->s_die);
		sem_post(man->table->s_eat);
		exit (1);
	}
	sem_post(man->table->s_eat);
	return (0);
}

void	set_lasteat(t_man *man)
{
	sem_wait(man->table->s_lasteat);
	man->lasteat = ft_time();
	sem_post(man->table->s_lasteat);
}

void	*monitor(t_man *man)
{
	while (true)
	{
		if (fill_monitor(man) == 1 || death_monitor(man) == 1)
			break ;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:54:07 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:54:09 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_open(t_table *table)
{
	table->s_lasteat = sem_open(SLASTEAT, O_CREAT, 0777, 1);
	table->forks = sem_open(SFORKS, O_CREAT, 0777, table->man_cnt);
	table->s_write = sem_open(SWRITE, O_CREAT, 0777, 1);
	table->s_die = sem_open(SDIE, O_CREAT, 0777, 1);
	table->s_eat = sem_open(SEAT, O_CREAT, 0777, 1);
	if (table->s_die == SEM_FAILED || table->forks == SEM_FAILED
		|| table->s_write == SEM_FAILED || table->s_lasteat == SEM_FAILED
		|| table->s_die == SEM_FAILED)
	{
		free(table->men);
		ft_exit_error("Semaphore error");
	}
}

static void	men_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->man_cnt)
	{
		table->men[i].id = i;
		table->men[i].lasteat = LONG_MAX;
		table->men[i].meal_counter = 0;
		table->men[i].dead_flg = &(table->dead_flg);
		table->men[i].table = table;
		table->men[i].start_tm = &(table->start_tm);
	}
}

void	ft_unlink(t_table *table)
{
	sem_close(table->s_lasteat);
	sem_unlink(SLASTEAT);
	sem_close(table->forks);
	sem_unlink(SFORKS);
	sem_close(table->s_write);
	sem_unlink(SWRITE);
	sem_close(table->s_die);
	sem_unlink(SDIE);
	sem_close(table->s_eat);
	sem_unlink(SEAT);
}

void	data_init(t_table *table)
{
	table->dead_flg = false;
	table->men = (t_man *)malloc(sizeof(t_man) * table->man_cnt);
	if (!table->men)
		ft_exit_error("Malloc error");
	men_init(table);
	ft_unlink(table);
	ft_sem_open(table);
}

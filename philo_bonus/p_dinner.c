/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dinner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:55:07 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:55:09 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_dinner(t_man *man)
{
	pthread_create(&man->thread, NULL, (void *)monitor, man);
	set_lasteat(man);
	while (1)
	{
		sem_wait(man->table->forks);
		progress_log(TAKE_FORK, man);
		sem_wait(man->table->forks);
		progress_log(TAKE_FORK, man);
		progress_log(EAT, man);
		ft_sleep(man->table->eat_tm);
		sem_post(man->table->forks);
		sem_post(man->table->forks);
		sem_wait(man->table->s_die);
		man->meal_counter++;
		sem_post(man->table->s_die);
		progress_log(SLEEP, man);
		set_lasteat(man);
		ft_sleep(man->table->sleep_tm);
		if (!man->table->dead_flg)
			progress_log(THINK, man);
	}
	pthread_join(man->thread, NULL);
	exit (0);
}

void	begin_dinner(t_table *table)
{
	int	i;
	int	status;

	i = -1;
	table->start_tm = ft_time();
	while (++i < table->man_cnt)
	{
		table->men[i].pid = fork();
		if (table->men[i].pid == 0)
			ft_dinner(&table->men[i]);
	}
	i = -1;
	while (++i < table->man_cnt)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) > 0)
		{
			i = -1;
			while (++i < table->man_cnt)
				kill(table->men[i].pid, SIGKILL);
			break ;
		}
	}
	ft_unlink(table);
	free(table->men);
}

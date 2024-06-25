/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:54:19 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:54:22 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit_error(char *error)
{
	printf(RED"%s\n"R, error);
	exit(EXIT_FAILURE);
}

char	*incorrect_input_msg(void)
{
	return ("Incorrect input. Provide\n\
 * number_of_philosophers\n * time_to_die\n\
 * time_to_eat\n * time_to_sleep\n\
 * number_of_tms_each_philosopher_meals_cnt (optional)");
}

void	progress_log(t_progress event, t_man *man)
{
	if (event == DIE)
		printf(RED"%ld	%d died\n"R, (ft_time() - *(man->start_tm)) / 1000, man->id + 1);
	else
	{
		sem_wait(man->table->s_write);
		if (event == TAKE_FORK)
			printf(P"%ld	%d has taken a fork\n"R, (ft_time() - *(man->start_tm)) / 1000, man->id + 1);
		else if (event == EAT)
			printf(Y"%ld	%d is eating\n"R, (ft_time() - *(man->start_tm)) / 1000, man->id + 1);
		else if (event == SLEEP)
			printf(B"%ld	%d is sleeping\n"R, (ft_time() - *(man->start_tm)) / 1000, man->id + 1);
		else if (event == THINK)
			printf(G"%ld	%d is thinking\n"R, (ft_time() - *(man->start_tm)) / 1000, man->id + 1);
	}
	sem_post(man->table->s_write);
}

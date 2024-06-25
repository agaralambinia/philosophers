/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:54:32 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:54:34 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

long	ft_atol(const char *s)
{
	long	res;

	res = 0;
	while (*s >= 48 && *s <= 57)
	{
		res = res * 10 - 48 + *s++;
		if (res > INT_MAX)
			ft_exit_error("Incorrect input. INT_MAX is limit.");
	}
	return (res);
}

long	ft_time(void)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_exit_error("Error: gettimeofday function failed.");
	return (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
}

void	ft_sleep(long tm)
{
	long	asleep;

	asleep = ft_time();
	while (ft_time() - asleep < tm * 1000)
	{
		if (ft_time() - asleep > 10000)
			usleep((ft_time() - asleep) / 2);
		else
		{
			while (ft_time() - asleep < tm * 1000)
				;
		}
	}
}

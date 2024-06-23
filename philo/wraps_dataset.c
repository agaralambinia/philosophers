/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wraps_dataset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: defimova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:49:23 by defimova          #+#    #+#             */
/*   Updated: 2024/06/23 19:49:41 by defimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_bool(pthread_mutex_t *mutex, bool *dst, bool v)
{
	ft_mutex(mutex, LOCK);
	*dst = v;
	ft_mutex(mutex, UNLOCK);
}

bool	ft_read_bool(pthread_mutex_t *mutex, bool *dst)
{
	bool	result;

	ft_mutex(mutex, LOCK);
	result = *dst;
	ft_mutex(mutex, UNLOCK);
	return (result);
}

void	ft_write_long(pthread_mutex_t *mutex, long *dst, long v)
{
	ft_mutex(mutex, LOCK);
	*dst = v;
	ft_mutex(mutex, UNLOCK);
}

void	ft_plus_long(pthread_mutex_t *mutex, long *dst)
{
	ft_mutex(mutex, LOCK);
	(*dst)++;
	ft_mutex(mutex, UNLOCK);
}

long	ft_read_long(pthread_mutex_t *mutex, long *dst)
{
	long	result;

	ft_mutex(mutex, LOCK);
	result = *dst;
	ft_mutex(mutex, UNLOCK);
	return (result);
}

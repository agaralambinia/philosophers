#include "philo_bonus.h"

long	ft_get_time(t_time code)
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

void ft_usleep(long usec, t_man *man)
{
	long	asleep;
	long	spent;
	long	left;

	spent = 0;
	asleep = ft_get_time(USEC);
	while (spent < usec)
	{
		if (man->finish_flg == true)
			break ;
		spent = ft_get_time(USEC) - asleep;
		left = usec - spent;
		if (left > 1000)
			usleep(left / 2);
		else
		{
			while (ft_get_time(USEC) - asleep < usec)
				 ;
		}
	}
}

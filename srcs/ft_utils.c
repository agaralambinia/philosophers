#include "../incs/philosophers.h"

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

void	*ft_malloc(size_t b)
{
	void	*res;

	res = malloc(b);
	if (res == NULL)
		ft_exit_error("Malloc error.");
	return (res);
}

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

void ft_usleep(long usec, t_table *table)
{
	long	asleep;
	long	spent;
	long	left;

	spent = 0;
	asleep = ft_get_time(MSEC);
	while (spent < usec)
	{
		if (dinner_finished(table))
			break ;
		spent = ft_get_time(MSEC) - asleep;
		left = usec - spent;
		if (left > 1000)
			usleep(left / 2);
		else
		{
			while (spent < usec)
				;
		}
	}
}

void	wait_beginning(t_table *table)
{
	while (!ft_read_bool(&table->table_mutex, &table->men_ready))
		;
}
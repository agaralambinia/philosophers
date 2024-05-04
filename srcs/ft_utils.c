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
		ft_exit_error("Malloc error.")
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
}
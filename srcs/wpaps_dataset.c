#include "../incs/philosophers.h"

void	ft_write_bool(pthread_mutex_t *mutex, bool *dst, bool v)
{
	ft_mutex(mutex, LOCK);
	*dst = v;
	ft_mutex(mutex, UNLOCK);
}

void	ft_read_bool(pthread_mutex_t *mutex, bool *dst)
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

void	ft_read_long(pthread_mutex_t *mutex, long *dst)
{
	long	result;
	ft_mutex(mutex, LOCK);
	result = *dst;
	ft_mutex(mutex, UNLOCK);
	return (result);
}

bool	dinner_finisher(t_table *table)
{
	return (ft_read_bool(&table->table_mutex, &table->end_flg));
}
#include "../incs/philosophers.h"

void	ft_write_bool(pthread_mutex_t *mutex, bool *dst, bool v)
{
	ft_mutex(mutex, LOCK);
	*dst = v;
	ft_mutex(mutex, UNLOCK);
}

bool	ft_read_bool(pthread_mutex_t *mutex, bool *dst)
{
	bool	result;
	//printf("DEBUG wraps_dataset %d\n", __LINE__);
	ft_mutex(mutex, LOCK);
	//printf("DEBUG wraps_dataset %d\n", __LINE__);
	result = *dst;
	//printf("DEBUG wraps_dataset %d\n", __LINE__);
	ft_mutex(mutex, UNLOCK);
	//printf("DEBUG wraps_dataset %d\n", __LINE__);
	return (result);
}

void	ft_write_long(pthread_mutex_t *mutex, long *dst, long v)
{
	ft_mutex(mutex, LOCK);
	*dst = v;
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

bool	dinner_finished(t_table *table)
{
	return (ft_read_bool(&table->table_mutex, &table->end_flg));
}
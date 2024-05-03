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

void	*ft_mutex_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == LOCK || code == UNLOCK || code == DESTROY))
		ft_exit_error("The value specified by mutex is invalid.");
	else if (status == EINVAL && code == INIT)
		ft_exit_error("The value specified by attr is invalid.");
	else if (status == ENOMEM && code == INIT)
		ft_exit_error(" \
The process cannot allocate enough memory to create another mutex.");
	else if (status == EDEADLK && code == LOCK)
		ft_exit_error(" \
A deadlock would occur if the thread blocked waiting for mutex.");
	else if (status == EPERM && code == UNLOCK)
		ft_exit_error("The current thread does not hold a lock on mutex.");
	else if (status == EBUSY && code == DESTROY)
		ft_exit_error("Mutex is locked.");
}

void	*ft_mutex(pthread_mutex_t *m, t_code code)
{
	if (code == LOCK)
		ft_mutex_error(pthread_mutex_lock(m));
	else if (code == UNLOCK)
		ft_mutex_error(pthread_mutex_unlock(m));
	else if (code == INIT)
		ft_mutex_error(pthread_mutex_init(m, NULL));
	else if (code == DESTROY)
		ft_mutex_error(pthread_mutex_destroy(m));
	else
		ft_exit_error("Mutex opcode Error.");
}
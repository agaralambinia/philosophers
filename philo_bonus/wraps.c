#include "philo_bonus.h"

void	ft_thread_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == JOIN || code == DETACH))
		ft_exit_error("The implementation has detected that the value \
specified by thread does not refer to a joinable thread.");
	else if (status == ESRCH && (code == JOIN || code == DETACH))
		ft_exit_error("No thread could be found corresponding to that \
specified by the given thread ID, thread.");
	else if (status == EDEADLK && code == JOIN)
		ft_exit_error("\
A deadlock was detected or the value of thread specifies the calling thread.");
	else if (status == EAGAIN && code == CREATE)
		ft_exit_error("The system lacked the necessary resources to create \
another thread, or the system-imposed limit on the total number of threads in \
a process [PTHREAD_THREADS_MAX] would be exceeded.");
	else if (status == EPERM && code == CREATE)
		ft_exit_error("The caller does not have appropriate permission to set \
the required scheduling parameters or scheduling policy.");
	else if (status == EINVAL && code == CREATE)
		ft_exit_error("The value specified by attr is invalid.");
}

void	ft_thread(pthread_t *t, void *(*f)(void *), void *val, t_code code)
{
	if (code == JOIN)
		ft_thread_error(pthread_join(*t, NULL), code);
	else if (code == DETACH)
		ft_thread_error(pthread_detach(*t), code);
	else if (code == CREATE)
		ft_thread_error(pthread_create(t, NULL, f, val), code);
	else
		ft_exit_error("Wrong thread code, should be JOIN, DETACH or CREATE");
}

void	*ft_malloc(size_t b)
{
	void	*res;

	res = malloc(b);
	if (res == NULL)
		ft_exit_error("Malloc error.");
	return (res);
}

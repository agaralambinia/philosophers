#include "../incs/philosophers.h"

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
		ft_mutex_error(pthread_mutex_lock(m), code);
	else if (code == UNLOCK)
		ft_mutex_error(pthread_mutex_unlock(m), code);
	else if (code == INIT)
		ft_mutex_error(pthread_mutex_init(m, NULL), code);
	else if (code == DESTROY)
		ft_mutex_error(pthread_mutex_destroy(m), code);
	else
		ft_exit_error("Mutex opcode Error.");
}

void	*ft_thread_error(int status, t_code code)
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

void	*ft_thread(pthread_t *t, void *(*f)(void *), void *val, t_code code)
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

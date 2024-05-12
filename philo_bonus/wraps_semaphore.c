#include "philo_bonus.h"

void	ft_thread_error(int status, t_code code)
{
	if (status == 0)
		return ;
	else if (status == EACCES && code == UNLINK)
		ft_exit_error("Permission is denied to be remove the semaphore.");
	else if (status == EACCES && code == OPEN)
		ft_exit_error("The required permissions (for reading and/or writing) \
are denied for the given flags; or O_CREAT is specified, the object does \
not exist, and permission to create the semaphore is denied.");
	else if (status == ENAMETOOLONG && code == UNLINK)
		ft_exit_error("name exceeded PSEMNAMLEN characters.");
	else if (status == ENOENT && code == UNLINK)
		ft_exit_error("The named semaphore does not exist.");
	else if (status == EEXIST && code == OPEN)
		ft_exit_error("\
O_CREAT and O_EXCL were specified and the semaphore exists.");
	else if (status == EINTR && code == OPEN)
		ft_exit_error("\
The sem_open() operation was interrupted by a signal.");
	else if (status == EINVAL && code == OPEN)
		ft_exit_error("The shm_open() operation is not supported; or \
O_CREAT is specified and value exceeds SEM_VALUE_MAX.");
	else if (status == EMFILE && code == OPEN)
		ft_exit_error("\
Too many semaphores or file descriptors are open on the system.");
	else if (status == ENOENT && code == OPEN)
		ft_exit_error("\
O_CREAT is not set and the named semaphore does not exist.");
	else if (status == ENOSPC && code == OPEN)
		ft_exit_error("O_CREAT is specified, the file does not exist \
and there is insufficient space available to create the semaphore.");
	else:
		return (status);
}

void	ft_semaphore(char *name, int oflag, int value, t_code code)
{
	if (code == UNLINK)
		ft_semaphore_error(sem_unlink(name), code);
	else if (code == OPEN && oflag == O_CREAT)
		ft_semaphore_error(sem_open(name, O_CREAT, 777, value), code);
	else if (code == OPEN && oflag == O_EXCL)
		ft_semaphore_error(sem_open(name, O_EXCL), code);
	else if (code == CLOSE)
		ft_thread_error(sem_close(t, NULL, f, val), code);
	else if (code == POST)
		ft_thread_error(sem_post(t, NULL, f, val), code);
	else if (code == WAIT)
		ft_thread_error(sem_wait(t, NULL, f, val), code);
	else
		ft_exit_error("Wrong thread code, should be JOIN, DETACH or CREATE");
}

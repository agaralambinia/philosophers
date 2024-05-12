#include "philo_bonus.h"

const char	*validate_input(const char *s)
{
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	while (*s == '+')
		s++;
	if (*s == '-')
		ft_exit_error("Incorrect input. Give positive numbers, please.");
	if (*s > '9' || *s < '0')
		ft_exit_error("Incorrect input. Give numbers, please.");
	return (s);
}

t_man *data_init(int argc, char **argv)
{
	t_man	*temp;

	temp = ft_malloc(sizeof(t_man));
	temp->man_cnt = ft_atol(validate_input(argv[1]));
	if (temp->man_cnt == 0)
		ft_exit_error("There can't be 0 philos, it's worthless!");
	temp->fork_cnt = temp->man_cnt;
	temp->t_die = ft_atol(validate_input(argv[2]));
	temp->t_eat = ft_atol(validate_input(argv[3]));
	temp->t_sleep = ft_atol(validate_input(argv[4]));
	if (argv[5])
		table->meals_cnt = ft_atol(validate_input(argv[5]));
	else
		table->meals_cnt = -1;
	temp->eaten_meals_cnt = 0;
	temp->stop = 0;
	return (temp);
}

t_man	*man_init(int argc, char **argv)
{
	t_man	*temp;

	temp = data_init(argc, argv);
	temp->pid = ft_malloc(sizeof(long) * temp->num_forks);
	sem_unlink("/block_print"); //TODO
	sem_unlink("/block_forks"); //TODO
	temp->block_printf = sem_open("/block_print", O_CREAT, 0644, 1);
	temp->block_fork = sem_open("/block_forks", O_CREAT, \
								0644, temp->num_forks);
	if (temp->block_printf <= 0 || temp->block_fork <= 0)
		ft_error("Error: semaphore open error");
	return (temp);
}
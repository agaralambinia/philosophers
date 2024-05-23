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

t_man *data_init(char **argv)
{
	t_man	*temp;

	temp = ft_malloc(sizeof(t_man));
	temp->man_cnt = ft_atol(validate_input(argv[1]));
	if (temp->man_cnt == 0)
		ft_exit_error("There can't be 0 philos, it's worthless!");
	temp->fork_cnt = temp->man_cnt;
	temp->die_tm = ft_atol(validate_input(argv[2]));
	temp->eat_tm = ft_atol(validate_input(argv[3]));
	temp->sleep_tm = ft_atol(validate_input(argv[4]));
	if (argv[5])
		temp->meals_cnt = ft_atol(validate_input(argv[5]));
	else
		temp->meals_cnt = -1;
	temp->eaten_meals_cnt = 0;
	temp->finish_flg = false;
	temp->die_flg = false;
	printf("DEBUG die_tm %lu\n", temp->die_tm);
	printf("DEBUG eat_tm %lu\n", temp->eat_tm);
	printf("DEBUG sleep_tm %lu\n", temp->sleep_tm);
	return (temp);
}

t_man	*man_init(char **argv)
{
	t_man	*temp;

	temp = data_init(argv);
	temp->pid = ft_malloc(sizeof(long) * temp->fork_cnt);
	sem_unlink("/out");
	sem_unlink("/fork");
	temp->out = sem_open("/out", O_CREAT, 0644, 1);
	temp->fork = sem_open("/fork", O_CREAT, 0644, temp->fork_cnt);
	if (temp->out <= 0 || temp->fork <= 0)
		ft_exit_error("Semaphore open error");
	return (temp);
}
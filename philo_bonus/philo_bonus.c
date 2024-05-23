#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_man	*man;
	int		i;

	if (argc == 5 || argc == 6)
	{
		man = man_init(argv);
		i = -1;
		printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
		man->start_tm = ft_get_time(USEC);
		printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
		while (++i < man->man_cnt)
		{
			printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
			man->pid[i] = fork();
			if (man->pid[i] == -1)
				ft_exit_error("Fork mistake");
			if (man->pid[i] == 0)
			{
				printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
				man->man_id = i + 1;
				man->eat_tm = ft_get_time(USEC);
				printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
				begin_dinner(man);
				printf("DEBUG	%d	%s\n", __LINE__, __FILE__);
			}
		}
	clean(&man);
	}
	else
		ft_exit_error(incorrect_input_msg());
	return (0);
}
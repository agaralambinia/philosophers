#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_man	*man;
	int		i;

	if (argc == 5 || argc == 6)
	{
		man = man_init(argv);
		i = -1;
		man->start_tm = ft_get_time(MSEC);
		while (++i < man->man_cnt)
		{
			man->pid[i] = fork();
			if (man->pid[i] == -1)
				ft_exit_error("Fork mistake");
			man->man_id = i + 1;
			man->eat_tm = ft_get_time(MSEC);
			begin_dinner(man);
		}
	clean(&man);
	}
	else
		ft_exit_error(incorrect_input_msg());
	return (0);
}

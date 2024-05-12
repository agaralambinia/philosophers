#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_man	*man;
	int		i;

	if (argc == 5 || argc == 6)
	{
		man = man_init(argc, argv); //TODO
	}
	else
		ft_exit_error(incorrect_input_msg());
	return (0);
}

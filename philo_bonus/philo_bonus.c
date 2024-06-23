#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	parse_input(argc, argv, &table);
	data_init(&table);
	begin_dinner(&table);
}

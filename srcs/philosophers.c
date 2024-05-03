#include "../incs/philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		begin_dinner(&table); //TODO
		clean(&table); //TODO
	}
	else
		ft_exit_error(incorrect_input_msg());
	
}
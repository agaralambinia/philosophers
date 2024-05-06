#include "../incs/philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	//printf("DEBUG philosophers %d\n", __LINE__);
	if (argc == 5 || argc == 6)
	{
		//printf("DEBUG philosophers %d\n", __LINE__);
		parse_input(&table, argv);
		//printf("DEBUG philosophers %d\n", __LINE__);
		data_init(&table);
		//printf("DEBUG philosophers %d\n", __LINE__);
		begin_dinner(&table);
		//printf("DEBUG philosophers %d\n", __LINE__);
		//clean(&table); //TODO
	}
	else
		ft_exit_error(incorrect_input_msg());
	
}
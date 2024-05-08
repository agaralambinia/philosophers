#include "../incs/philosophers.h"

int	main(int argc, char **argv)
{
	printf("DEBUG	%d	%s\n", __LINE__, __FILE__); //TODO
	t_table	table;
	if (argc == 5 || argc == 6)
	{
		printf("DEBUG	%d	%s\n", __LINE__, __FILE__); //TODO
		parse_input(&table, argv);
		printf("DEBUG	%d	%s\n", __LINE__, __FILE__); //TODO
		data_init(&table);
		printf("DEBUG	%d	%s\n", __LINE__, __FILE__); //TODO
		begin_dinner(&table);
		printf("DEBUG	%d	%s\n", __LINE__, __FILE__); //TODO
		clean(&table);
		printf("DEBUG	%d	%s\n", __LINE__, __FILE__); //TODO
	}
	else
		ft_exit_error(incorrect_input_msg());
	return (0);
}
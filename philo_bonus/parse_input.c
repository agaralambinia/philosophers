#include "philo_bonus.h"

static const char	*validate_input(const char *s)
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

void	parse_input(int argc, char *argv[], t_table *table)
{
	if (argc < 5 || argc > 6)
		ft_exit_error(incorrect_input_msg());
	table->man_cnt = ft_atol(validate_input(argv[1]));
	table->die_tm = ft_atol(validate_input(argv[2]));
	table->eat_tm = ft_atol(validate_input(argv[3]));
	table->sleep_tm = ft_atol(validate_input(argv[4]));
	if (argc == 6)
		table->meals_cnt = ft_atol(argv[5]);
	else
		table->meals_cnt = -1;
	if (table->die_tm < 60 || table->eat_tm < 60 || table->sleep_tm < 60)
		ft_exit_error("Incorrect input. Timestamp must be > 60ms.");
	if (table->man_cnt <= 0)
		ft_exit_error("There can't be 0 or less men, it's worthless!");
	if (argc == 6 && table->meals_cnt <= 0)
		ft_exit_error("Please provide amount of mandatory meals > 0!");
}

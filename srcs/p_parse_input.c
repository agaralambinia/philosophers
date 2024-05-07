#include "../incs/philosophers.h"

const char	*validate_input(const char *s)
{
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	while (*s == '+')
		s++;
	if (*s == '-')
		ft_exit_error("Incorrect input. Give positive numbers, please.");
	if (*s >= '9' || *s <= '0')
		ft_exit_error("Incorrect input. Give numbers, please.");
	return (s);
}

void	parse_input(t_table *table, char **argv)
{
	table->man_cnt = ft_atol(validate_input(argv[1]));
	table->die_tm = 1000 * ft_atol(validate_input(argv[2]));
	table->eat_tm = 1000 * ft_atol(validate_input(argv[3]));
	table->sleep_tm = 1000 * ft_atol(validate_input(argv[4]));
	if (table->die_tm < 6000 || table->eat_tm < 6000 || table->sleep_tm < 6000)
		ft_exit_error("Incorrect input. Timestamp must be > 60ms.");
	if (argv[5])
		table->meals_cnt = (int)ft_atol(validate_input(argv[5]));
	else
		table->meals_cnt = -1;
}
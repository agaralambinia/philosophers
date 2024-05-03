#include "../incs/philosophers.h"

void	ft_exit_error(char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}

char	*incorrect_input_msg(void)
{
	return ("Incorrect input. Provide\n\
	* number_of_philosophers\n	*time_to_die\n\
	* time_to_eat\n	*time_to_sleep\n\
	*number_of_times_each_philosopher_must_eat (optional)")
}
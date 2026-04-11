#include "philo.h"

void	check_if_died(t_data *data)
{
	size_t		i;
	size_t		current_time;
	size_t		last_meal;

	i = 0;
	while (i < data->num_philos)
	{
		current_time = get_time();
		last_meal = data->philos[i].last_meal;
		if (current_time - last_meal > data->t_die)
		{
			pthread_mutex_lock(&data->writing);
			output_die(&(data->philos[i]));
			pthread_mutex_unlock(&data->writing);
			data->someone_died = TRUE;
			return ;
		}
		i++;
	}
}

void	check_if_eaten_enough(t_data *data)
{
	size_t	i;

	if (data->must_eat == 0)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
			return ;
		i++;
	}
	data->someone_died = TRUE;
}

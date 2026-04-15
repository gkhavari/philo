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
		pthread_mutex_lock(&data->meal_check);
		last_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->meal_check);
		if (current_time - last_meal > data->t_die)
		{
			output_die(&(data->philos[i]));
			pthread_mutex_lock(&data->death_check);
			data->end_simulation = TRUE;
			pthread_mutex_unlock(&data->death_check);
			return ;
		}
		i++;
	}
}

/*Call only with locked meal_check*/
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
	pthread_mutex_lock(&data->death_check);
	data->end_simulation = TRUE;
	pthread_mutex_unlock(&data->death_check);
}

void	monitor_simulation(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->death_check);
		if (data->end_simulation)
		{
			pthread_mutex_unlock(&data->death_check);
			break ;
		}
		pthread_mutex_unlock(&data->death_check);
		check_if_died(data);
		pthread_mutex_lock(&data->meal_check);
		check_if_eaten_enough(data);
		pthread_mutex_unlock(&data->meal_check);
		usleep(1000);
	}
}

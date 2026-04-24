#include "philo.h"

int	get_start_simulation(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->simulation_mutex);
	value = data->start_simulation;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (value);
}

void	set_start_simulation(t_data *data, int value)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->start_simulation = value;
	pthread_mutex_unlock(&data->simulation_mutex);
}

int	get_end_simulation(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->simulation_mutex);
	value = data->end_simulation;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (value);
}

void	set_end_simulation(t_data *data, int value)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->end_simulation = value;
	pthread_mutex_unlock(&data->simulation_mutex);
}
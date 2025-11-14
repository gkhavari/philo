#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (!philo->is_dead)
	{
		long long now = get_time();
		long long time_since_last_meal = now - philo->last_meal;

		if (time_since_last_meal >= philo->data->t_die)
		{
			pthread_mutex_lock(&philo->data->writing);
			printf("%lld %d died\n", now - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->writing);
			philo->is_dead = 1;
			break;
		}
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	pthread_t threads[data->num_philos];
	size_t i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = data->start_time;
		pthread_create(&threads[i], NULL, philo_routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
		pthread_join(threads[i++], NULL);
}

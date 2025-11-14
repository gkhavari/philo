#include "philo.h"

/*returns time in millisecond*/
long long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long) tv.tv_usec / 1000);
}

void	free_all(t_data *data)
{
	size_t	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free (data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->meal_check);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

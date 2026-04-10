/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:25:16 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/10 16:25:18 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo		*philo;
	long long	now;
	long long	time_since_last_meal;

	philo = (t_philo *)arg;
	while (!philo->data->someone_died)
	{
		now = get_time();
		time_since_last_meal = now - philo->last_meal;
		if (time_since_last_meal >= philo->data->t_die)
		{
			pthread_mutex_lock(&philo->data->writing);
			printf("%lld %d died\n", now - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->writing);
			philo->data->someone_died = 1;
			break ;
		}
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	pthread_t	threads[data->num_philos];
	size_t		i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = data->start_time;
		pthread_create(&threads[i], NULL, philo_routine, &data->philos[i]);
		if (data->someone_died == 1)
			return ;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
		pthread_join(threads[i++], NULL);
}

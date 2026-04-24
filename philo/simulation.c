/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:25:16 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/15 22:21:55 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** Creates philosopher threads, uses simulation mutex on failure, 
 * returns number of threads created */
static size_t	create_threads(t_data *data)
{
	size_t	created;

	created = 0;
	while (created < data->num_philos)
	{
		if (pthread_create(&data->philos[created].thread, NULL,
				philo_routine, &data->philos[created]) != 0)
		{
			pthread_mutex_lock(&data->simulation_mutex);
			data->end_simulation = TRUE;
			pthread_mutex_unlock(&data->simulation_mutex);
			break ;
		}
		created++;
	}
	return (created);
}

/** Joins created threads */
static void	join_threads(t_data *data, size_t created)
{
	size_t	i;

	i = 0;
	while (i < created)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

/** Starts the simulation, creates and joins threads, calls monitoring */
void	start_simulation(t_data *data)
{
	size_t	created;
	size_t	i;

	created = create_threads(data);
	if (created != data->num_philos)
	{
		data->end_simulation = TRUE;
		join_threads(data, created);
		return ;
	}
	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].state_mutex);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->philos[i].state_mutex);
		i++;
	}
	set_start_simulation(data, TRUE);
	if (data->num_philos != 1)
		monitor_simulation(data);
	join_threads(data, created);
}

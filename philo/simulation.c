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

	data->start_time = get_time();
	created = create_threads(data);
	if (created != data->num_philos)
	{
		join_threads(data, created);
		return ;
	}
	if (data->num_philos == 1)
	{
		join_threads(data, data->num_philos);
		return ;
	}
	monitor_simulation(data);
	join_threads(data, created);
}

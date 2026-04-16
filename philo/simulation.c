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

static void	handle_single_philo(t_data *data)
{
	if (data->num_philos == 1)
	{
		my_msleep(data->t_die);
		output_die(&(data->philos[0]));
		pthread_mutex_lock(&data->death_check);
		data->end_simulation = TRUE;
		pthread_mutex_unlock(&data->death_check);
	}
}

/*returns number of threads created*/
static size_t	create_threads(t_data *data)
{
	size_t	created;

	created = 0;
	while (created < data->num_philos)
	{
		if (pthread_create(&data->philos[created].thread, NULL,
				philo_routine, &data->philos[created]) != 0)
		{
			pthread_mutex_lock(&data->death_check);
			data->end_simulation = TRUE;
			pthread_mutex_unlock(&data->death_check);
			break ;
		}
		created++;
	}
	return (created);
}

/*makes sure to only join created threads*/
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

void	start_simulation(t_data *data)
{
	size_t	created;

	handle_single_philo(data);
	data->start_time = get_time();
	created = create_threads(data);
	if (created != data->num_philos)
	{
		join_threads(data, created);
		return ;
	}
	monitor_simulation(data);
	join_threads(data, created);
}

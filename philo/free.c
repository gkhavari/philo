/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 20:55:32 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/21 20:55:34 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_forks(t_data *data)
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
}

static void	destroy_philo_mutex(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].state_mutex);
		i++;
	}
}

void	free_all(t_data *data)
{
	free_forks(data);
	if (data->philos)
		destroy_philo_mutex(data);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->simulation_mutex);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

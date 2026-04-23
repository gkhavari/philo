/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:22:13 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/15 22:22:15 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** Checks if simulation should end, uses simulation mutex */
int	end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->simulation_mutex);
	if (data->end_simulation == TRUE)
	{
		pthread_mutex_unlock(&data->simulation_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&data->simulation_mutex);
	return (FALSE);
}

/** Monitors for philosopher deaths, uses state mutexes and simulation mutex */
static void	check_philosopher_death(t_data *data)
{
	size_t		i;
	size_t		current_time;

	i = 0;
	while (i < data->num_philos)
	{
		current_time = get_time();
		pthread_mutex_lock(&data->philos[i].state_mutex);
		if (end_simulation(data) == TRUE)
		{
			pthread_mutex_unlock(&data->philos[i].state_mutex);
			return ;
		}
		if (current_time - data->philos[i].last_meal >= data->t_die)
		{
			print_status(&(data->philos[i]), DIE_MSG);
			pthread_mutex_lock(&data->simulation_mutex);
			data->end_simulation = TRUE;
			pthread_mutex_unlock(&data->simulation_mutex);
			pthread_mutex_unlock(&data->philos[i].state_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->philos[i].state_mutex);
		i++;
	}
}

/** Checks if all philosophers ate enough, uses state mutexes 
 * and simulation mutex */
static void	check_if_eaten_enough(t_data *data)
{
	size_t	i;

	if (data->must_eat == 0)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].state_mutex);
		if (data->philos[i].meals_eaten < data->must_eat)
		{
			pthread_mutex_unlock(&data->philos[i].state_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->philos[i].state_mutex);
		i++;
	}
	if (i == data->num_philos)
	{
		pthread_mutex_lock(&data->simulation_mutex);
		data->end_simulation = TRUE;
		pthread_mutex_unlock(&data->simulation_mutex);
		return ;
	}
}

/** Runs monitoring loop, calls death and meal checks */
void	monitor_simulation(t_data *data)
{
	while (1)
	{
		check_if_eaten_enough(data);
		check_philosopher_death(data);
		if (end_simulation(data) == TRUE)
			break ;
	}
}

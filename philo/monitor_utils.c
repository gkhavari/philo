/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 22:14:55 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/24 22:14:58 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** Gets the start_simulation flag safely using mutex */
int	get_start_simulation(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->simulation_mutex);
	value = data->start_simulation;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (value);
}

/** Sets the start_simulation flag safely using mutex */
void	set_start_simulation(t_data *data, int value)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->start_simulation = value;
	pthread_mutex_unlock(&data->simulation_mutex);
}

/** Gets the end_simulation flag safely using mutex */
int	get_end_simulation(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->simulation_mutex);
	value = data->end_simulation;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (value);
}

/** Sets the end_simulation flag safely using mutex */
void	set_end_simulation(t_data *data, int value)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->end_simulation = value;
	pthread_mutex_unlock(&data->simulation_mutex);
}

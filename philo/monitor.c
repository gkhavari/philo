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

/*returns value of end_simulation flag, uses mutex death check*/
int	end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->death_check);
	if (data->end_simulation == TRUE)
	{
		pthread_mutex_unlock(&data->death_check);
		return (TRUE);
	}
	pthread_mutex_unlock(&data->death_check);
	return (FALSE);
}

void	check_if_died(t_data *data)
{
	size_t		i;
	size_t		current_time;

	i = 0;
	while (i < data->num_philos)
	{
		current_time = get_time();
		pthread_mutex_lock(&data->meal_check);
		if (end_simulation(data) == TRUE)
		{
			pthread_mutex_unlock(&data->meal_check);
			return ;
		}
		if (current_time - data->philos[i].last_meal >= data->t_die)
		{
			print_status(&(data->philos[i]), DIE_MSG);
			pthread_mutex_lock(&data->death_check);
			data->end_simulation = TRUE;
			pthread_mutex_unlock(&data->death_check);
			pthread_mutex_unlock(&data->meal_check);
			return ;
		}
		pthread_mutex_unlock(&data->meal_check);
		i++;
	}
}

/*Call only with locked meal_check*/
void	check_if_eaten_enough(t_data *data)
{
	size_t	i;

	if (data->must_eat == 0)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&data->death_check);
	data->end_simulation = TRUE;
	pthread_mutex_unlock(&data->death_check);
}

void	monitor_simulation(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->death_check);
		if (data->end_simulation)
		{
			pthread_mutex_unlock(&data->death_check);
			break ;
		}
		pthread_mutex_unlock(&data->death_check);
		pthread_mutex_lock(&data->meal_check);
		check_if_eaten_enough(data);
		pthread_mutex_unlock(&data->meal_check);
		if (end_simulation(data) == TRUE)
			break ;
		check_if_died(data);
	}
}

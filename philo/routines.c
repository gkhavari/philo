/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:38:08 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/15 22:38:26 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*single_philo_routine(t_philo *philo)
{
	print_status(philo, FORK_MSG);
	my_msleep(philo->data->t_die);
	print_status(philo, DIE_MSG);
	pthread_mutex_lock(&philo->data->simulation_mutex);
	philo->data->end_simulation = TRUE;
	pthread_mutex_unlock(&philo->data->simulation_mutex);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		return (single_philo_routine(philo));
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->data->simulation_mutex);
		if (philo->data->end_simulation == TRUE)
		{
			pthread_mutex_unlock(&philo->data->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->simulation_mutex);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_return_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

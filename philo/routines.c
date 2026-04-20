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

/*Even Philosophers eat -> sleep -> think*/
static void	routine_even(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_check);
		if (philo->data->end_simulation == TRUE)
		{
			pthread_mutex_unlock(&philo->data->death_check);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_check);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_return_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

/*Last Philosophers think -> eat -> sleep*/
static void	routine_last(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_check);
		if (philo->data->end_simulation == TRUE)
		{
			pthread_mutex_unlock(&philo->data->death_check);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_check);
		philo_think(philo);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_return_forks(philo);
		philo_sleep(philo);
	}
}

void	*single_philo_routine(t_philo *philo)
{
	print_status(philo, FORK_MSG);
	my_msleep(philo->data->t_die);
	output_die(philo->data->philos);
	pthread_mutex_lock(&philo->data->death_check);
	philo->data->end_simulation = TRUE;
	pthread_mutex_unlock(&philo->data->death_check);
	return (NULL);
}

/*Odd Philosophers sleep -> think -> eat*/
static void	routine_odd(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_check);
		if (philo->data->end_simulation == TRUE)
		{
			pthread_mutex_unlock(&philo->data->death_check);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_check);
		philo_sleep(philo);
		philo_think(philo);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_return_forks(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->data->num_philos == 1)
	{
		single_philo_routine(philo);
		return (NULL);
	}
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		routine_even(philo);
	else if (philo->id == (int)philo->data->num_philos)
		routine_last(philo);
	else
		routine_odd(philo);
	return (NULL);
}

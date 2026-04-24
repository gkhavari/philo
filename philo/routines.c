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

/** Handles single philosopher case, takes one fork, waits to die, 
 * uses simulation mutex */
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

/** Waits until simulation start signal or early termination */
static void	wait_for_start(t_philo *philo)
{
	while (get_start_simulation(philo->data) != TRUE
		&& get_end_simulation(philo->data) != TRUE)
		usleep(500);
}

/** Initializes philosopher state: sets last meal time and 
 * increments ready philosopher count */
static void	init_philo_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->data->simulation_mutex);
	philo->data->ready_philos += 1;
	pthread_mutex_unlock(&philo->data->simulation_mutex);
}

/** Applies stagger delay to even-numbered philosophers to 
 * reduce contention at start */
static void	handle_stagger(t_philo *philo)
{
	size_t	stagger;

	if (philo->id % 2 == 0)
	{
		stagger = (philo->data->t_eat + philo->data->t_sleep)
			/ philo->data->num_philos;
		my_msleep_stop(philo->data, stagger);
	}
}

/** Main philosopher thread routine: waits for start signal, 
 * initializes state, handles single philosopher case, 
 * staggers execution, then enters main activity loop 
 * repeats fork-taking, eating, 
 * releasing forks, sleeping, and thinking until simulation ends*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	init_philo_state(philo);
	if (philo->data->num_philos == 1)
		return (single_philo_routine(philo));
	handle_stagger(philo);
	while (1)
	{
		if (get_end_simulation(philo->data) == TRUE)
			break ;
		philo_take_forks(philo);
		philo_eat(philo);
		philo_return_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

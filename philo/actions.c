/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:21:29 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/15 22:21:31 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** Takes two forks in order, uses fork mutexes to prevent deadlock */
void	philo_take_forks(t_philo *philo)
{
	int	first;
	int	second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first]);
	print_status(philo, FORK_MSG);
	pthread_mutex_lock(&philo->data->forks[second]);
	print_status(philo, FORK_MSG);
}

/** Returns the two forks, unlocks fork mutexes */
void	philo_return_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

/** Simulates eating, updates last meal time and meal count with state mutex, 
 * sleeps for eat time */
void	philo_eat(t_philo *philo)
{
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->state_mutex);
	philo->meals_eaten++;
	print_status(philo, EAT_MSG);
	pthread_mutex_unlock(&philo->state_mutex);
	my_msleep(philo->data->t_eat);
}

/** Simulates sleeping, prints sleep status, sleeps for sleep time */
void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	my_msleep(philo->data->t_sleep);
}

/** Simulates thinking, prints think status, sleeps extra for odd philosopher 
 * count */
void	philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
	if (philo->data->num_philos % 2 == 1)
		my_msleep(philo->data->t_eat);
}

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

/*
Even philosophers take right fork first then left,
odd philosophers left fork first then right
*/
void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		philo->has_right_fork = TRUE;
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		philo->has_left_fork = TRUE;
		print_status(philo, FORK_MSG);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		philo->has_left_fork = TRUE;
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		philo->has_right_fork = TRUE;
		print_status(philo, FORK_MSG);
	}
}

void	philo_return_forks(t_philo *philo)
{
	if (philo->has_right_fork == TRUE)
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	if (philo->has_left_fork == TRUE)
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	philo->has_left_fork = FALSE;
	philo->has_right_fork = FALSE;
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_check);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	print_status(philo, EAT_MSG);
	pthread_mutex_unlock(&philo->data->meal_check);
	my_msleep(philo->data->t_eat);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	my_msleep(philo->data->t_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
	if (philo->data->num_philos % 2 == 1)
		my_msleep(philo->data->t_eat);
}

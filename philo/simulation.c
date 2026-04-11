/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:25:16 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/10 16:25:18 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_if_died(t_data *data)
{
	size_t		i;
	size_t		current_time;
	size_t		last_meal;

	i = 0;
	while (i < data->num_philos)
	{
		current_time = get_time();
		last_meal = data->philos[i].last_meal;
		if (current_time - last_meal > data->t_die)
		{
			pthread_mutex_lock(&data->writing);
			output_die(&(data->philos[i]));
			pthread_mutex_unlock(&data->writing);
			data->someone_died = TRUE;
			return ;
		}
		i++;
	}
}

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
	data->someone_died = TRUE;
}

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, FORK_MSG);

	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, FORK_MSG);
}

void	philo_return_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	philo_eat(t_philo *philo)
{
	print_status(philo, EAT_MSG);
	philo->last_meal = get_time();
	usleep(philo->data->t_eat * 1000);
	philo->meals_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	usleep(philo->data->t_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died)
	{
		philo_think(philo);
		philo_take_forks(philo);
		philo_eat(philo);
		philo_return_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	size_t	i;

	if(data->num_philos == 1)
	{
		usleep(data->t_die);
		output_die(&(data->philos[0]));
		data->someone_died = 1;
	}
	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
		i++;
	}
	while (data->someone_died == FALSE)
	{
		check_if_died(data);
		check_if_eaten_enough(data);
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

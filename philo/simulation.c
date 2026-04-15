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

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// Phase offset: stagger initial actions
	if (philo->id % 2 == 0)
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
	else if (philo->id == (int)philo->data->num_philos)
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
	else
	{
		// Odd philosophers (except last) start thinking
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
	return (NULL);
}

static void	handle_single_philo(t_data *data)
{
	if (data->num_philos == 1)
	{
		usleep(data->t_die);
		output_die(&(data->philos[0]));
		pthread_mutex_lock(&data->death_check);
		data->end_simulation = TRUE;
		pthread_mutex_unlock(&data->death_check);
	}
}

static void	create_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philo_routine, &data->philos[i]);
		i++;
	}
}

static void	join_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	start_simulation(t_data *data)
{
	handle_single_philo(data);
	data->start_time = get_time();
	create_threads(data);
	monitor_simulation(data);
	join_threads(data);
}

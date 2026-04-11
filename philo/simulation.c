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

static void	handle_single_philo(t_data *data)
{
	if (data->num_philos == 1)
	{
		usleep(data->t_die);
		output_die(&(data->philos[0]));
		data->someone_died = TRUE;
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

static void	monitor_simulation(t_data *data)
{
	while (data->someone_died == FALSE)
	{
		check_if_died(data);
		check_if_eaten_enough(data);
		usleep(1000);
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

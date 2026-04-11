/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:16:47 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/10 16:16:49 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	size_t	i;

	i = 0;
	data->num_philos = (size_t)ft_atoi_simple(argv[1]);
	data->t_die = (size_t)ft_atoi_simple(argv[2]);
	data->t_eat = (size_t)ft_atoi_simple(argv[3]);
	data->t_sleep = (size_t)ft_atoi_simple(argv[4]);
	if (argc == 6)
		data->must_eat = (size_t)ft_atoi_simple(argv[5]);
	else
		data->must_eat = 0;
	data->start_time = get_time();
	data->someone_died = FALSE;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return ;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->writing, NULL);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return ;
}

void	init_philos(t_data *data)
{
	size_t	i;

	i = 0;
	memset(data->philos, 0, sizeof(t_philo) * data->num_philos);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
}

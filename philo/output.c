/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:05:06 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/10 20:05:09 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->writing);
	if (!philo->data->someone_died)
	{
		time = get_time() - philo->data->start_time;
		printf("%zu %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->writing);
}

void	output_take_fork(t_data *data, long long time, int philo)
{
	if (data->someone_died)
		return;
	printf("%lld %d has taken a fork", time, philo);
}

void	output_eat(t_data *data, long long time, int philo)
{
	if (data->someone_died)
		return;
	printf("%lld %d is eating", time, philo);
}

void	output_sleep(t_data *data, long long time, int philo)
{
	if (data->someone_died)
		return;
	printf("%lld %d is sleeping", time, philo);
}

void	output_think(t_data *data, long long time, int philo)
{
	if (data->someone_died)
		return;
	printf("%lld %d is thinking", time, philo);
}

void	output_die(t_philo *philo)
{
	size_t time;

	time = get_time() - philo->data->start_time;
	printf("%zu %d died\n", time, philo->id);
}

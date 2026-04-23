/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:26:46 by gkhavari          #+#    #+#             */
/*   Updated: 2026/04/10 16:26:48 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** Returns current time in milliseconds */
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long) tv.tv_usec / 1000);
}

/** Sleeps for specified milliseconds using usleep */
void	my_msleep(long milliseconds)
{
	long long	start;

	start = get_time();
	while (get_time() - start < milliseconds)
	{
		usleep(500);
	}
}

/** Sleeps for specified milliseconds using usleep, but only as long as 
 * the simulation does not stop*/
void	my_msleep_stop(t_data *data, long milliseconds)
{
	long	start;

	start = get_time();
	while (!end_simulation(data))
	{
		if (get_time() - start >= milliseconds)
			break ;
		usleep(500);
	}
}

/** Prints philosopher status message, uses simulation and print mutexes 
 * for thread safety */
void	print_status(t_philo *philo, char *msg)
{
	size_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->simulation_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->end_simulation == FALSE || ft_strcmp(msg, DIE_MSG) == 0)
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->simulation_mutex);
}

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

	pthread_mutex_lock(&philo->data->death_check);
	pthread_mutex_lock(&philo->data->writing);
	if (philo->data->end_simulation == TRUE)
	{
		pthread_mutex_unlock(&philo->data->writing);
		pthread_mutex_unlock(&philo->data->death_check);
		return ;
	}
	time = get_time() - philo->data->start_time;
	printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->writing);
	pthread_mutex_unlock(&philo->data->death_check);
}

void	output_die(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->writing);
	printf("%zu %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->writing);
}

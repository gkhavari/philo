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

/*Prints corresponding status message, uses writing mutex*/
void	print_status(t_philo *philo, char *msg)
{
	size_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->simulation_mutex);
	if (philo->data->end_simulation == FALSE || strcmp(msg, DIE_MSG) == 0)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%zu %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->simulation_mutex);
}

/*Prints death status message, uses writing mutex*/
void	output_die(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%zu %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

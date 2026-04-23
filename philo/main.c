/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:08:53 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/13 18:08:55 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** Entry point, checks input, initializes data, starts simulation, frees resources */
int	main(int argc, char **argv)
{
	t_data	data;

	if (input_check(argc, argv))
		return (EXIT_FAILURE);
	memset(&data, 0, sizeof(data));
	init_data(&data, argc, argv);
	if (!data.forks || !data.philos)
	{
		printf("Error: Malloc failure\n");
		free_all(&data);
		return (EXIT_FAILURE);
	}
	init_philos(&data);
	start_simulation(&data);
	free_all(&data);
	return (EXIT_SUCCESS);
}

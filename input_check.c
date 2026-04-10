/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:09:03 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/13 18:09:05 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_single_arg(const char *arg, const char *name)
{
	int	val;
	int	error;

	error = 0;
	if (!ft_isdigit_str(arg))
	{
		printf("Error: %s must be a positive integer\n", name);
		error = 1;
	}
	else
	{
		val = ft_atoi_simple(arg);
		if (val == ATOI_ERROR)
		{
			printf("Error: invalid value for %s (must be > 0 and <= INT_MAX)\n",
				name);
			error = 1;
		}
	}
	return (error);
}

static void	print_usage(const t_arg_info *g_args)
{
	printf("Usage: ./philo %s %s %s %s [%s]\n",
		g_args[ARG_NUM_PHILOS].name,
		g_args[ARG_TIME_DIE].name,
		g_args[ARG_TIME_EAT].name,
		g_args[ARG_TIME_SLEEP].name,
		g_args[ARG_NUM_EAT].name
		);
}

int	input_check(int argc, char **argv)
{
	int						error;
	int						i;
	static const t_arg_info	g_args[ARG_COUNT] = {
	[ARG_NUM_PHILOS] = {"number_of_philosophers"},
	[ARG_TIME_DIE] = {"time_to_die"},
	[ARG_TIME_EAT] = {"time_to_eat"},
	[ARG_TIME_SLEEP] = {"time_to_sleep"},
	[ARG_NUM_EAT] = {"number_of_times_each_philosopher_must_eat"}
	};

	error = 0;
	if (argc != 5 && argc != 6)
	{
		if (argc > 1 && ft_strcmp(argv[1], HELP_FLAG))
			printf("Error: wrong number of arguments\n");
		print_usage(g_args);
		return (1);
	}
	i = ARG_NUM_PHILOS;
	while (i < argc)
	{
		error += check_single_arg(argv[i], g_args[i].name);
		i++;
	}
	return (error);
}

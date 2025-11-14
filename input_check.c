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

long	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX || (sign == -1 && result > INT_MAX - 1))
			return ((long)INT_MAX + 1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	ft_isdigit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_single_arg(const char *arg, const char *name)
{
	long	val;
	int		error;

	error = 0;
	if (!ft_isdigit_str(arg))
	{
		printf("Error: %s must be a positive integer\n", name);
		error = 1;
	}
	else
	{
		val = ft_atoi(arg);
		if (val <= 0 || val > INT_MAX)
		{
			printf("Error: %s must be > 0 and <= INT_MAX\n", name);
			error = 1;
		}
	}
	return (error);
}

int	input_check(int argc, char **argv)
{
	int	error;

	error = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	error += check_single_arg(argv[1], "number_of_philosophers");
	error += check_single_arg(argv[2], "time_to_die");
	error += check_single_arg(argv[3], "time_to_eat");
	error += check_single_arg(argv[4], "time_to_sleep");
	if (argc == 6)
		error += check_single_arg(argv[5],
				"number_of_times_each_philosopher_must_eat");
	return (error);
}

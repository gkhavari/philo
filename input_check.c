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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
			printf("Error: invalid value for %s (must be > 0 and <= INT_MAX)\n",
				name);
			error = 1;
		}
	}
	return (error);
}

void	print_usage(const t_arg_info *g_args)
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

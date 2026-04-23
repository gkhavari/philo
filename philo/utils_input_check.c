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

/** Converts string to int, handles overflow */
int	ft_atoi_simple(const char *str)
{
	size_t	i;
	int		result;
	int		digit;

	if (!str)
		return (ATOI_ERROR);
	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > (INT_MAX - digit) / 10)
			return (ATOI_ERROR);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

/** Checks if string consists only of digits */
int	ft_isdigit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (FALSE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/** Compares two strings lexicographically */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

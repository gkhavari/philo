/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:08:46 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/13 18:08:48 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h> //für memset
# include <stdio.h> // für printf
# include <sys/time.h>

# define INT_MAX 2147483647
# define HELP_FLAG "--help"
# define TRUE 1
# define FALSE 0
# define ATOI_ERROR -1

typedef struct s_arg_info
{
	const char	*name;
}	t_arg_info;

enum	e_args
{
	ARG_NUM_PHILOS = 1,
	ARG_TIME_DIE,
	ARG_TIME_EAT,
	ARG_TIME_SLEEP,
	ARG_NUM_EAT,
	ARG_COUNT
};

typedef struct s_philo	t_philo;

typedef struct s_data
{
	size_t			num_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	long long		start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	long long	last_meal;
	int			meals_eaten;
	t_data		*data;
}	t_philo;

int			input_check(int argc, char **argv);
void		init_data(t_data *data, int argc, char **argv);
void		init_philos(t_data *data);
void		start_simulation(t_data *data);
long long	get_time(void);
void		free_all(t_data *data);
int			ft_atoi_simple(const char *str);
int			ft_isdigit_str(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isdigit_str(const char *str);

#endif

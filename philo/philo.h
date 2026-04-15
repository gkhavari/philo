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
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdatomic.h>

# define INT_MAX 2147483647
# define HELP_FLAG "--help"
# define TRUE 1
# define FALSE 0
# define ATOI_ERROR -1
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"

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
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			must_eat;
	long long		start_time;
	int				end_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	death_check;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				left_fork;
	int				right_fork;
	size_t			last_meal;
	size_t			meals_eaten;
	t_data			*data;
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
void		output_die(t_philo *philo);
void		print_status(t_philo *philo, char *msg);
void		philo_take_forks(t_philo *philo);
void		philo_return_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		check_if_died(t_data *data);
void		check_if_eaten_enough(t_data *data);
void		monitor_simulation(t_data *data);

#endif

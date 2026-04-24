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

# define INT_MAX 2147483647
# define HELP_FLAG "--help"
# define USAGE_DETAILS "\nnum_philosophers: The number of philosophers and forks.\n\
time_to_die: Time in milliseconds after which a philosopher dies if they haven't \
started eating.\n\
time_to_eat: Time in milliseconds it takes for a philosopher to eat.\n\
time_to_sleep: Time in milliseconds a philosopher spends sleeping.\n\
times_must_eat (optional): The number of times each philosopher must eat before \
the simulation stops. If not provided, the simulation runs until a philosopher \
dies.\n"
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
	int				start_simulation;
	int				end_simulation;
	size_t			ready_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simulation_mutex;
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
	pthread_mutex_t	state_mutex;
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
void		print_status(t_philo *philo, char *msg);
void		philo_take_forks(t_philo *philo);
void		philo_return_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		monitor_simulation(t_data *data);
void		my_msleep(long milliseconds);
void		*philo_routine(void *arg);
void		my_msleep_stop(t_data *data, long milliseconds);
int			get_start_simulation(t_data *data);
void		set_start_simulation(t_data *data, int value);
int			get_end_simulation(t_data *data);
void		set_end_simulation(t_data *data, int value);

#endif

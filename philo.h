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

typedef struct s_arg_info
{
	const char *name;
} t_arg_info;

enum	e_args
{
	ARG_NUM_PHILOS = 1,
	ARG_TIME_DIE,
	ARG_TIME_EAT,
	ARG_TIME_SLEEP,
	ARG_NUM_EAT,
	ARG_COUNT
};

typedef struct s_philo t_philo;

typedef struct s_data
{
	size_t			num_philos;     // Number of philosophers
	int				t_die;     // Max time without eating
	int				t_eat;     // Time spent eating
	int				t_sleep;   // Time spent sleeping
	int				must_eat;       // Optional: number of meals
	long long		start_time;      // Simulation start timestamp
	int				someone_died;
	pthread_mutex_t	*forks;          // Array of mutexes for forks
	pthread_mutex_t	writing;         // Mutex for printing
	pthread_mutex_t	meal_check;      // Mutex for accessing last_meal
	t_philo			*philos;        // Array of philosopher structs
} t_data;

typedef struct s_philo
{
	int			id;             // Philosopher ID
	int			left_fork;      // Index of left fork
	int			right_fork;     // Index of right fork
	long long	last_meal;      // Timestamp of last meal
	int			meals_eaten;    // Count of meals eaten
	t_data		*data;          // Pointer to shared data
} t_philo;

int			input_check(int argc, char **argv);
void 		init_data(t_data *data, int argc, char **argv);
void 		init_philos(t_data *data);
void		start_simulation(t_data *data);
long long	get_time(void);
void		free_all(t_data *data);


#endif

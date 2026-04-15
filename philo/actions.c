#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
	// Even philosophers: right fork first, then left
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, FORK_MSG);
	}
	else
	{
		// Odd philosophers: left fork first, then right
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, FORK_MSG);
	}
}

void	philo_return_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_check);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_check);
	print_status(philo, EAT_MSG);
	usleep(philo->data->t_eat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	usleep(philo->data->t_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
	usleep(philo->data->t_eat * 100);
}

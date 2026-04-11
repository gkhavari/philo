#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, FORK_MSG);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, FORK_MSG);
}

void	philo_return_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	philo_eat(t_philo *philo)
{
	print_status(philo, EAT_MSG);
	philo->last_meal = get_time();
	usleep(philo->data->t_eat * 1000);
	philo->meals_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	usleep(philo->data->t_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}

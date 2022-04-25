#include "philo_bonus.h"

void	eat(t_philos **philo)
{
	int	last_meal;

	last_meal = 0;
	sem_wait((*philo)->data->forks);
	sem_wait((*philo)->data->forks);
	sem_wait((*philo)->data->printer);
	printf("%d %d has taken a fork\n", get_time((*philo)->data->begin), (*philo)->id);
	printf("%d %d has taken a fork\n", get_time((*philo)->data->begin), (*philo)->id);
	sem_post((*philo)->data->printer);
	last_meal = get_time((*philo)->data->begin);
	(*philo)->last_meal = last_meal;
	sem_wait((*philo)->data->printer);
	printf("%d %d is eating\n", last_meal, (*philo)->id);
	sem_post((*philo)->data->printer);
	// (*meals)++;
	ft_usleep((*philo)->data->time_to_eat, (*philo)->data->begin);
	sem_post((*philo)->data->forks);
	sem_post((*philo)->data->forks);
}

void	sleep_and_think(t_philos **philo)
{
	sem_wait((*philo)->data->printer);
	printf("%d %d is sleeping\n", get_time((*philo)->data->begin), (*philo)->id);
	sem_post((*philo)->data->printer);
	ft_usleep((*philo)->data->time_to_sleep, (*philo)->data->begin);
	sem_wait((*philo)->data->printer);
	printf("%d %d is thinking\n", get_time((*philo)->data->begin), (*philo)->id);
	sem_post((*philo)->data->printer);
}

#include "philo_bonus.h"

void	eat(t_philos **philo)
{
	int	last_meal;

	last_meal = 0;
	sem_wait((*philo)->data->forks);
	sem_wait((*philo)->data->forks);
	printf("%d %d has taken a fork\n", get_time((*philo)->data->begin), (*philo)->id);
	printf("%d %d has taken a fork\n", get_time((*philo)->data->begin), (*philo)->id);
	last_meal = get_time((*philo)->data->begin);
	(*philo)->last_meal = last_meal;
	printf("%d %d is eating\n", last_meal, (*philo)->id);
	ft_usleep((*philo)->data->time_to_eat, (*philo)->data->begin);
	sem_post((*philo)->data->forks);
	sem_post((*philo)->data->forks);
}

void	sleep_and_think(t_philos **philo)
{
	printf("%d %d is sleeping\n", get_time((*philo)->data->begin), (*philo)->id);
	ft_usleep((*philo)->data->time_to_sleep, (*philo)->data->begin);
	printf("%d %d is thinking\n", get_time((*philo)->data->begin), (*philo)->id);
}

#include "philo_bonus.h"

int	check_death(t_philos *philos)
{
	int	time_to_die;

	time_to_die = philos->data->time_to_die;
	if (get_time(philos->data->begin) - philos->last_meal > time_to_die)
	{
		printf("%d %d died\n", get_time(philos->data->begin), philos->id);
		return (1);
	}
	return (0);
}

void	food_police(t_philos **philos)
{
	int	nbr_of_meals;
	int	i;

	nbr_of_meals = (*philos)->data->nbr_of_meals;
	i = 0;
	while (i < (*philos)->data->nbr_of_philo)
	{
		if ((*philos)[i].meals != nbr_of_meals)
		{
			printf("philo %d only ate %d times\n", (*philos)[i].id, (*philos)[i].meals);
			return ;
		}
		i++;
	}
	sem_close((*philos)->data->forks);
	printf("ALL PHILOS ATE\n");
	exit(EXIT_SUCCESS);
}

void	death_police(t_philos **philos)
{
	int	i;

	i = 0;
	while (i < (*philos)->data->nbr_of_philo)
	{
		if (check_death(&(*philos)[i]) == 1)
		{
			sem_close((*philos)->data->forks);
			kill(-1, SIGKILL);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	*police_thread(void *philo)
{
	t_philos	*ph;

	ph = (t_philos *)philo;
	while (1)
	{
		death_police(&ph);
	}
}
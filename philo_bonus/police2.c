#include "philo_bonus.h"

void	*deathsignal(void *philos)
{
	t_philos	**philo;
	int			time_to_die;
	int			i;

	philo = (t_philos **)&philos;
	time_to_die = (*philo)->data->time_to_die;
	i = 0;
	while (1)
	{
		if (get_time((*philo)->data->begin) > ((*philo)->last_meal + time_to_die))
		{
			sem_wait((*philo)->data->printer);
			printf("%d %d died\n", get_time((*philo)->data->begin), (*philo)->id);
			sem_close((*philo)->data->forks);
			sem_close((*philo)->data->printer);
			while (i < (*philo)->data->nbr_of_philo)
			{
				kill((*philo)->data->sons[i], SIGINT);
				i++;
			}
			exit(EXIT_FAILURE);
		}
	}
}

void	food_police(t_philos **philos)
{
	int	i;

	i = 0;
	while (i < (*philos)->data->nbr_of_philo)
	{
		// printf("philo number %d ate %d times and should eat %d times\n", (*philos)[i].id, (*philos)[i].meals, (*philos)->data->nbr_of_meals);
		if ((*philos)[i].meals < (*philos)->data->nbr_of_meals)
			return ;
		i++;
	}
	sem_wait((*philos)->data->printer);
	printf("%d philosophers ate %d times\n", (*philos)->data->nbr_of_philo, (*philos)->data->nbr_of_meals);
	sem_close((*philos)->data->forks);
	sem_close((*philos)->data->printer);
	while (i < (*philos)->data->nbr_of_philo)
	{
		kill((*philos)->data->sons[i], SIGINT);
		i++;
	}
	exit(EXIT_SUCCESS);
}

// void	stop_simulation(t_philos **philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < (*philos)->data->nbr_of_philo)
// 	{
// 		if ((*philos)[i].life == 0)
// 		{
// 			kill(-1, SIGKILL);
// 			printf("%d %d died\n", get_time((*philos)->data->begin), (*philos)[i].id);
// 			sem_close((*philos)->data->forks);
// 			sem_unlink("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// }

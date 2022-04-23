#include "philo_bonus.h"

void	*deathsignal(void *philos)
{
	t_philos	**philo;
	int			time_to_die;

	philo = (t_philos **)&philos;
	time_to_die = (*philo)->data->time_to_die;
	while (1)
	{
		if (get_time((*philo)->data->begin) > ((*philo)->last_meal + time_to_die))
		{
			printf("%d %d died\n", get_time((*philo)->data->begin), (*philo)->id);
			sem_close((*philo)->data->forks);
			sem_unlink("FORKSEM");
			kill(0, SIGSTOP);
			exit(EXIT_FAILURE);
		}
	}
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

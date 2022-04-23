#include "philo_bonus.h"

void	create_philo(t_philos *philo)
{
	int			i;
	pid_t		pid;
	pthread_t	watcher;

	i = 0;
	pid = fork();
	if (pid == -1)
		send_error(&(philo->data), FORK_ERROR);
	if (pid == 0) // on est dans le fils
	{
		pthread_create(&watcher, NULL, deathsignal, philo);
		if (philo->data->nbr_of_meals != 0)
		{
			while (philo->meals < philo->data->nbr_of_meals)
			{
				eat(&philo);
				(philo->meals)++;
				sleep_and_think(&philo);
			}
		}
		else
		{
			while (1)
			{
				eat(&philo);
				(philo->meals)++;
				sleep_and_think(&philo);
			}
		}
		// exit(EXIT_SUCCESS); // finir par un exit sinon le fils va revenir dans la boucle du main et recréer un fork
		sem_close(philo->data->forks);
		waitpid(-1, NULL, 0);
	}
}

int main(int argc, char **argv)
{
	t_data		*data;
	t_philos	*philos;
	int			i;

	parse_args(argc, argv, &data);
	init_structs(&data, &philos);
	i = 0;
	data->forks = sem_open("FORKSEM", O_CREAT, S_IRWXU, data->nbr_of_forks);
	gettimeofday(&data->begin, NULL);
	while (i < data->nbr_of_philo)
	{
		// printf("i = %d et nbr of philo = %d\n", i, data->nbr_of_philo);
		// printf("Creation of philo number %d starting...\n", philos[i].id);
		create_philo(&philos[i]);
		i++;
	}
	// while (1)
	// {
	// 	stop_simulation(&philos);
	// 	// printf("checking for death\n");
	// }
	waitpid(0, NULL, 0);
	// sem_unlink("forks");
	// while (1)
	// {
	// }
}

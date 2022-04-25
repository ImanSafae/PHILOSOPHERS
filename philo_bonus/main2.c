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
		pthread_detach(watcher);
		while (1)
		{
			eat(&philo);
			(philo->meals)++;
			sleep_and_think(&philo);
		}
		// exit(EXIT_SUCCESS); // finir par un exit sinon le fils va revenir dans la boucle du main et recréer un fork
		sem_close(philo->data->forks);
	}
	else
		(philo->data->sons)[(philo->id) - 1] = pid;
}

int main(int argc, char **argv)
{
	t_data		*data;
	t_philos	*philos;
	int			i;

	parse_args(argc, argv, &data);
	init_structs(&data, &philos);
	i = 0;
	sem_unlink("FORKS");
	sem_unlink("PRINTER");
	data->forks = sem_open("FORKS", O_CREAT, S_IRWXU, data->nbr_of_forks);
	data->printer = sem_open("PRINTER", O_CREAT, S_IRWXU, 1);
	gettimeofday(&data->begin, NULL);
	while (i < data->nbr_of_philo)
	{
		// printf("i = %d et nbr of philo = %d\n", i, data->nbr_of_philo);
		// printf("Creation of philo number %d starting...\n", philos[i].id);
		create_philo(&philos[i]);
		i++;
	}
	i = 0;
	while (data->nbr_of_meals != 0)
	{
		while (i < data->nbr_of_philo)
		{
			printf("philo %d's last meal = %d\n", philos[i].id, philos[i].last_meal);
			i++;
		}
		i = 0;
		food_police(&philos);
	}
	// while (i < data->nbr_of_philo)
	// {
	// 	waitpid(data->sons[i], NULL, 0);
	// 	i++;
	// 
}

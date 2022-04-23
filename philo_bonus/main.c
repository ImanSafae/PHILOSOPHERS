/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:02:13 by itaouil           #+#    #+#             */
/*   Updated: 2022/04/09 15:02:14 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

void	philo_routine(t_philos *philo)
{
	pid_t		pid;
	// pthread_t	watcher;

	pid = fork();
	if (pid == 0) // un fils = un philo
	{
		// pthread_create(&watcher, NULL, police_thread, philo->data->philos);
		// pthread_detach(watcher);
		if (philo->data->nbr_of_meals != 0)
		{
			while (philo->meals < philo->data->nbr_of_meals)
			{
				eat(&philo);
				(philo->meals)++;
				sleep_and_think(&philo);
			}
			printf("philo abt to exit\n");
			exit(EXIT_SUCCESS);
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
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philos	*philos;
	int			i;

	i = 0;
	parse_args(argc, argv, &data);
	init_structs(&data, &philos);
	gettimeofday(&data->begin, NULL);
	data->forks = sem_open("forks", O_CREAT, S_IRWXU, data->nbr_of_forks);
	while (i < data->nbr_of_philo)
	{
		philo_routine(&philos[i]);
		i++;
		// printf("stuck in infinite loop\n");
	}
	while (data->nbr_of_meals != 0)
	{
		// death_police(&philos); à mettre dans un thread dans les processus correspondants
		// food_police(&philos);
		// printf("stuck in infinite loop\n");
	}
	// waitpid()
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:03:06 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/03 16:03:08 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_meals(t_data **data)
{
	int	i;
	int	nbr_philo;

	i = 0;
	nbr_philo = (*data)->nbr_of_philo;
	if ((*data)->nbr_of_meals != 0)
	{
		sem_unlink("MEALS");
		(*data)->meals = sem_open("MEALS", O_CREAT, S_IRWXU, nbr_philo);
		while (i < (*data)->nbr_of_philo)
		{
			sem_wait((*data)->meals);
			i++;
		}
		i = 0;
	}
}

void	set_semaphores(t_data **data)
{
	sem_unlink("FORKS");
	sem_unlink("PRINTER");
	(*data)->forks = sem_open("FORKS", O_CREAT, S_IRWXU, (*data)->nbr_of_forks);
	(*data)->printer = sem_open("PRINTER", O_CREAT, S_IRWXU, 1);
}

void	create_philo(t_philos *philo)
{
	int			i;
	pid_t		pid;
	pthread_t	watcher;

	i = 0;
	pid = fork();
	if (pid == -1)
		send_error(&(philo->data), FORK_ERROR);
	if (pid == 0)
	{
		pthread_create(&watcher, NULL, deathsignal, philo);
		pthread_detach(watcher);
		while (1)
		{
			eat(&philo);
			sleep_and_think(&philo);
			if (philo->data->nbr_of_meals != 0)
			{
				if (philo->meals == philo->data->nbr_of_meals)
					sem_post(philo->data->meals);
			}
		}
	}
	else
		(philo->data->sons)[(philo->id) - 1] = pid;
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philos	*philos;
	int			i;

	i = 0;
	parse_args(argc, argv, &data);
	init_structs(&data, &philos);
	set_semaphores(&data);
	set_meals(&data);
	gettimeofday(&data->begin, NULL);
	while (i < data->nbr_of_philo)
	{
		create_philo(&philos[i]);
		i++;
	}
	if (data->nbr_of_meals != 0)
		food_police(&data);
	else
		wait_for_sons(&data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:58:11 by itaouil           #+#    #+#             */
/*   Updated: 2022/03/14 12:58:12 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philos		*philos;
	int				i;

	if (!parse_args(argc, argv, &data, &philos))
		return (0);
	gettimeofday(&data->begin, NULL);
	i = 0;
	init_mutex(&data, &philos);
	while (i < data->nbr_of_philo)
	{
		philos[i].id = i + 1;
		pthread_create(&philos[i].philo, NULL, routine_philo, &philos[i]);
		pthread_detach(philos[i].philo);
		pthread_create(&(data->watchers[i]), NULL, death_watcher, &philos[i]);
		pthread_detach(data->watchers[i]);
		i++;
	}
	pthread_mutex_lock(&data->game_over);
	pthread_mutex_destroy(data->forks);
	pthread_mutex_unlock(&(philos->data->printer));
	pthread_mutex_destroy(&data->printer);
}

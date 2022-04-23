/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:41:47 by itaouil           #+#    #+#             */
/*   Updated: 2022/03/22 14:41:48 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	send_error(t_data **data, int error_code)
{
	if (error_code == 1)
		printf("Wrong argument\n");
	else if (error_code == 2)
		printf("Wrong number of arguments\n");
	free((*data));
}

int	check_non_numeric_args(int argc, char **argv, t_data **data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (no_numeric_chars(argv[i]))
		{
			send_error(data, 1);
			return (0);
		}
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) && !ft_isspace(argv[i][j]))
			{
				send_error(data, 1);
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv, t_data **data)
{
	if (argc != 5 && argc != 6)
	{
		send_error(data, 2);
		return (0);
	}
	if (!strncmp(argv[1], "0", 1))
		return (0);
	if (!check_non_numeric_args(argc, argv, data))
		return (0);
	return (1);
}

t_data	*parse_args(int argc, char **argv, t_data **data, t_philos **philos)
{
	int	i;

	i = 0;
	(*data) = malloc(sizeof(t_data));
	if (!check_args(argc, argv, data))
		return (0);
	(*data)->nbr_of_philo = ft_atoi(argv[1]);
	*philos = malloc(sizeof(t_philos) * (*data)->nbr_of_philo);
	(*data)->watchers = malloc(sizeof(pthread_t) * (*data)->nbr_of_philo);
	(*data)->philos = philos;
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	while (i < (*data)->nbr_of_philo)
	{
		(*philos)[i].data = (*data);
		(*philos)[i].meals = 0;
		(*philos)[i].life = 1;
		i++;
	}
	if (argv[5])
		(*data)->nbr_of_meals = ft_atoi(argv[5]);
	else
		(*data)->nbr_of_meals = 0;
	return ((*data));
}

void	init_mutex(t_data **data, t_philos **philos)
{
	int	i;

	i = 0;
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->nbr_of_philo);
	while (i < (*data)->nbr_of_philo)
	{
		pthread_mutex_init(&(*data)->forks[i], NULL);
		pthread_mutex_init(&((*philos)[i].cant_die), NULL);
		i++;
	}
	pthread_mutex_init(&(*data)->printer, NULL);
	pthread_mutex_init(&(*data)->game_over, NULL);
	pthread_mutex_lock(&(*data)->game_over);
}

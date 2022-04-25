/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:02:19 by itaouil           #+#    #+#             */
/*   Updated: 2022/04/09 15:02:20 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	send_error(t_data **data, int error_code)
{
	if (error_code == INVALID_ARGC)
		printf("Error: Wrong number of arguments.\n");
	else if (error_code == NON_NUMERIC_ARG)
		printf("Error: Non-numeric argument(s).\n");
	else if (error_code == NO_PHILO)
		printf("Error: There are no philosophers !\n");
	else if (error_code == NEGATIVE_VALUE)
		printf("Error: Negative value.\n");
	else if (error_code == FORK_ERROR)
		printf("Fork failed.\n");
	free((*data));
	exit(EXIT_FAILURE);
}

void	check_errors(int argc, char **argv, t_data **data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
		send_error(data, INVALID_ARGC);
	while (argv[i])
	{
		if (no_numeric_chars(argv[i]))
			send_error(data, NON_NUMERIC_ARG);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) && !ft_isspace(argv[i][j]))
			{
				if (argv[i][j] == '-')
					send_error(data, NEGATIVE_VALUE);
				else
					send_error(data, NON_NUMERIC_ARG);
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (ft_atoi(argv[1]) == 0)
		send_error(data, NO_PHILO);
}

void	parse_args(int argc, char **argv, t_data **data)
{
	check_errors(argc, argv, data);
	(*data) = malloc(sizeof(t_data));
	(*data)->nbr_of_philo = ft_atoi(argv[1]);
	(*data)->nbr_of_forks = (unsigned int)ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	(*data)->sons = malloc(sizeof(pid_t) * (*data)->nbr_of_philo);
	if (argv[5])
		(*data)->nbr_of_meals = ft_atoi(argv[5]);
	else
		(*data)->nbr_of_meals = 0;
}

void	init_structs(t_data **data, t_philos **philos)
{
	int	i;

	i = 0;
	(*philos) = malloc(sizeof(t_philos) * (*data)->nbr_of_philo);
	while (i < (*data)->nbr_of_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals = 0;
		(*philos)[i].last_meal = 0;
		(*philos)[i].data = (*data);
		i++;
	}
	(*data)->philos = philos;
}
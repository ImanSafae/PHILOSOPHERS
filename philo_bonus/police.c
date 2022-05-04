/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:02:38 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/03 16:02:39 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*deathsignal(void *philos)
{
	t_philos	**philo;
	int			time_to_die;
	int			i;
	int			id;

	philo = (t_philos **)&philos;
	time_to_die = (*philo)->data->time_to_die;
	i = 0;
	id = (*philo)->id;
	while (1)
	{
		if (get_time((*philo)->data->begin)
			> ((*philo)->last_meal + time_to_die))
		{
			sem_wait((*philo)->data->printer);
			printf("%d %d died\n", get_time((*philo)->data->begin), id);
			sem_close((*philo)->data->forks);
			while (i < (*philo)->data->nbr_of_philo)
			{
				kill((*philo)->data->sons[i], SIGINT);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
	}
}

void	food_police(t_data **data)
{
	int	i;
	int	nbr_philo;

	i = 0;
	nbr_philo = (*data)->nbr_of_philo;
	sem_wait((*data)->meals);
	sem_wait((*data)->printer);
	printf("%d philosophers ate %d times\n", nbr_philo, (*data)->nbr_of_meals);
	sem_close((*data)->meals);
	while (i < nbr_philo)
	{
		kill((*data)->sons[i], SIGINT);
		i++;
	}
}

void	wait_for_sons(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->nbr_of_philo - 1)
	{
		waitpid((*data)->sons[i], NULL, 0);
		i++;
	}
}

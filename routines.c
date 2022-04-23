/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:09:55 by itaouil           #+#    #+#             */
/*   Updated: 2022/03/31 18:09:56 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	all_philos_ate(t_philos **philos)
{
	int	i;
	int	nbr_of_philo;
	int	nbr_of_meals;

	i = 0;
	nbr_of_philo = (*philos)->data->nbr_of_philo;
	nbr_of_meals = (*philos)->data->nbr_of_meals;
	while (i < nbr_of_philo)
	{
		if ((*philos)[i].meals != nbr_of_meals)
			return (0);
		i++;
	}
	pthread_mutex_lock(&(*philos)->data->printer);
	printf("%d philosophers ate %d times\n", nbr_of_philo, nbr_of_meals);
	return (1);
}

void	*death_watcher(void *ph)
{
	t_philos	**philo;
	int			time_to_die;
	int			id;

	philo = (t_philos **)&ph;
	time_to_die = (*philo)->data->time_to_die;
	id = (*philo)->id;
	while (1)
	{
		if ((get_time((*philo)->data->begin))
			> ((*philo)->last_meal + time_to_die))
		{
			pthread_mutex_lock(&(*philo)->cant_die);
			if ((get_time((*philo)->data->begin))
				> ((*philo)->last_meal + time_to_die))
			{
				pthread_mutex_lock(&(*philo)->data->printer);
				printf("%d %d died\n", get_time((*philo)->data->begin), id);
				pthread_mutex_unlock(&(*philo)->data->game_over);
				return (NULL);
			}
			else
				pthread_mutex_unlock(&(*philo)->cant_die);
		}
	}
}

void	food_police(t_philos **philo, int right_fork, int left_fork)
{
	while ((*philo)->meals < (*philo)->data->nbr_of_meals)
	{
		eat(philo, right_fork, left_fork, &(*philo)->meals);
		sleep_and_think(philo);
	}
	while (1)
	{
		if (all_philos_ate(philo))
		{
			pthread_mutex_unlock(&(*philo)->data->game_over);
			return ;
		}
	}
}

void	*routine_philo(void	*ph)
{
	int			left_fork;
	int			right_fork;
	t_philos	**philo;

	philo = (t_philos **)&ph;
	left_fork = (*philo)->id - 1;
	if ((*philo)->id == 1)
		right_fork = ((*philo)->data->nbr_of_philo) - 1;
	else
		right_fork = (*philo)->id - 2;
	if ((*philo)->id % 2 == 0)
		ft_usleep((*philo)->data->time_to_eat, (*philo)->data->begin);
	if ((*philo)->data->nbr_of_meals == 0)
	{
		while (1)
		{
			eat(philo, right_fork, left_fork, &(*philo)->meals);
			sleep_and_think(philo);
		}
	}
	else if ((*philo)->data->nbr_of_meals != 0)
		food_police(philo, right_fork, left_fork);
	return (NULL);
}

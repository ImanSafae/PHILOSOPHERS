/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:02:58 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/03 16:02:59 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philos **philo)
{
	int	last_meal;
	int	id;

	last_meal = 0;
	id = (*philo)->id;
	sem_wait((*philo)->data->forks);
	sem_wait((*philo)->data->forks);
	sem_wait((*philo)->data->printer);
	printf("%d %d has taken a fork\n", get_time((*philo)->data->begin), id);
	printf("%d %d has taken a fork\n", get_time((*philo)->data->begin), id);
	sem_post((*philo)->data->printer);
	last_meal = get_time((*philo)->data->begin);
	(*philo)->last_meal = last_meal;
	sem_wait((*philo)->data->printer);
	printf("%d %d is eating\n", last_meal, id);
	sem_post((*philo)->data->printer);
	((*philo)->meals)++;
	ft_usleep((*philo)->data->time_to_eat, (*philo)->data->begin);
	sem_post((*philo)->data->forks);
	sem_post((*philo)->data->forks);
}

void	sleep_and_think(t_philos **philo)
{
	sem_wait((*philo)->data->printer);
	printf("%d %d is sleeping\n", get_time((*philo)->data->begin), (*philo)->id);
	sem_post((*philo)->data->printer);
	ft_usleep((*philo)->data->time_to_sleep, (*philo)->data->begin);
	sem_wait((*philo)->data->printer);
	printf("%d %d is thinking\n", get_time((*philo)->data->begin), (*philo)->id);
	sem_post((*philo)->data->printer);
}

// void	limited_meals(t_philos **philos)
// {
// 	while ((*philos)->meals < (*philos)->data->nbr_of_meals)
// 	{
// 		eat(philos);
// 		sleep_and_think(philos);
// 	}
// 	food_police(philos);
// }

// void	unlimited_meals(t_philos **philos)
// {
// 	while (1)
// 	{
// 		eat(philos);
// 		sleep_and_think(philos);
// 	}
// }

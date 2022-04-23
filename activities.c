/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:41:39 by itaouil           #+#    #+#             */
/*   Updated: 2022/03/22 14:41:40 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philos **philo, int right, int left, int *meals)
{
	int	id;

	id = (*philo)->id;
	pthread_mutex_lock(&(*philo)->data->forks[left]);
	pthread_mutex_lock(&(*philo)->data->forks[right]);
	pthread_mutex_lock(&(*philo)->data->printer);
	printf("%d %d has taken a fork\n", get_time((*philo)->data->begin), id);
	printf("%d %d has taken a fork\n", get_time((*philo)->data->begin), id);
	pthread_mutex_lock(&(*philo)->cant_die);
	(*philo)->last_meal = get_time((*philo)->data->begin);
	printf("%d %d is eating\n", get_time((*philo)->data->begin), id);
	pthread_mutex_unlock(&(*philo)->data->printer);
	(*meals)++;
	ft_usleep((*philo)->data->time_to_eat, (*philo)->data->begin);
	pthread_mutex_unlock(&(*philo)->data->forks[left]);
	pthread_mutex_unlock(&(*philo)->data->forks[right]);
	pthread_mutex_unlock(&(*philo)->cant_die);
}

void	sleep_and_think(t_philos **philo)
{
	int	id;

	id = (*philo)->id;
	pthread_mutex_lock(&(*philo)->data->printer);
	printf("%d %d is sleeping\n", get_time((*philo)->data->begin), id);
	pthread_mutex_unlock(&(*philo)->data->printer);
	ft_usleep((*philo)->data->time_to_sleep, (*philo)->data->begin);
	pthread_mutex_lock(&(*philo)->data->printer);
	printf("%d %d is thinking\n", get_time((*philo)->data->begin), id);
	pthread_mutex_unlock(&(*philo)->data->printer);
}

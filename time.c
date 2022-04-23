/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:39:56 by itaouil           #+#    #+#             */
/*   Updated: 2022/04/06 16:39:57 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	get_time(struct timeval begin)
{
	struct timeval	end;
	int				seconds;
	int				useconds;
	int				ms;

	gettimeofday(&end, NULL);
	seconds = end.tv_sec - begin.tv_sec;
	useconds = end.tv_usec - begin.tv_usec;
	ms = (seconds * 1000) + (useconds / 1000);
	return (ms);
}

void	ft_usleep(int ms, struct timeval begin)
{
	int	time;

	time = get_time(begin);
	while ((get_time(begin)) - time < ms)
		usleep(500);
}

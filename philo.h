/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:47:34 by itaouil           #+#    #+#             */
/*   Updated: 2022/03/31 16:47:37 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philos
{
	pthread_t		philo;
	pthread_mutex_t	cant_die;
	struct s_data	*data;
	int				id;
	int				meals;
	int				last_meal;
	int				life;
}			t_philos;

typedef struct s_data
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				i;
	struct timeval	begin;
	pthread_mutex_t	*forks;
	pthread_mutex_t	game_over;
	pthread_mutex_t	printer;
	t_philos		**philos;
	pthread_t		*watchers;
}			t_data;

// ROUTINES
void	*routine_philo(void	*ph);
void	*death_watcher(void *ph);
void	food_police(t_philos **philo, int right_fork, int left_fork);

// PARSING
t_data	*parse_args(int argc, char **argv, t_data **data, t_philos **philos);
int		check_args(int argc, char **argv, t_data **data);
int		ft_atoi(const char *str);
void	free_all(t_data **data);
void	send_error(t_data **data, int error_code);

// ACTIVITIES
void	eat(t_philos **philo, int right, int left, int *meals);
void	sleep_and_think(t_philos **philo);

// UTILS
int		get_time(struct timeval begin);
void	ft_usleep(int ms, struct timeval begin);
void	init_mutex(t_data **data, t_philos **philos);
int		all_philos_ate(t_philos **philos);
int		ft_isspace(char c);
int		ft_isdigit(int c);
int		no_numeric_chars(char *str);

#endif

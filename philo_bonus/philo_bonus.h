/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:43:41 by itaouil           #+#    #+#             */
/*   Updated: 2022/04/06 17:43:42 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_philos {
	int				id;
	int				meals;
	int				last_meal;
	struct s_data	*data;
}				t_philos;

typedef struct s_data {
	struct timeval	begin;
	int				nbr_of_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				nbr_of_meals;
	unsigned int	nbr_of_forks;
	t_philos		**philos;
	sem_t			*forks;
	sem_t			*printer;
	sem_t			*meals;
	pid_t			*sons;
}				t_data;

// ERROR CODES
# define INVALID_ARGC 1
# define NON_NUMERIC_ARG 2
# define NO_PHILO 3
# define NEGATIVE_VALUE 4
# define FORK_ERROR 5

// PARSING
void	parse_args(int argc, char **argv, t_data **data);
void	check_errors(int argc, char **argv, t_data **data);
void	send_error(t_data **data, int error_code);
void	init_structs(t_data **data, t_philos **philos);

// UTILS
int		ft_isspace(char c);
int		ft_isdigit(int c);
int		no_numeric_chars(char *str);
int		ft_atoi(const char *str);
void	wait_for_sons(t_data **data);

// TIME
int		get_time(struct timeval begin);
void	ft_usleep(int ms, struct timeval begin);

// ACTIVITIES
void	eat(t_philos **philo);
void	sleep_and_think(t_philos **philo);
void	unlimited_meals(t_philos **philos);
void	limited_meals(t_philos **philos);

// FOOD AND DEATH CHECKERS
void	food_police(t_data **data);
void	*deathsignal(void *philos);

#endif

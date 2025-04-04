/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:55:30 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/03 19:58:44 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\x1b[38;2;255;179;186m"
# define GREEN "\x1b[38;2;186;255;201m"
# define YELLOW "\x1b[38;2;255;255;186m"
# define BLUE "\x1b[38;2;186;225;255m"
# define PURPLE "\x1b[38;2;223;186;255m"
# define CYAN "\x1b[38;2;186;255;255m"
# define PINK "\x1b[38;2;255;186;255m"
# define RESET "\x1b[0m"

# define PHILO_MAX 200
# define ER STDERR_FILENO
# define DEBUG 1

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK,
	DIED,
}					t_status;

typedef enum e_mtx
{
	FULL,
	DEAD,
	MEAL,
	PRINT,
}					t_mtx;

typedef struct s_data
{
	__uint16_t		nbr_of_phils;
	__uint32_t		time_to_die;
	__uint32_t		time_to_eat;
	__uint32_t		time_to_sleep;
	__uint32_t		time_to_think;
	__uint16_t		must_eat_times;
	struct timeval	simul_start;
	int				philo_died;
	__uint16_t		fulled_phils;
	struct timeval	*last_meal;
	pthread_mutex_t	*mtx_fork;
	pthread_mutex_t	*mtx_full;
	pthread_mutex_t	*mtx_dead;
	pthread_mutex_t	*mtx_meal;
	pthread_mutex_t	*mtx_print;
}					t_data;

typedef struct s_philo
{
	int				id;
	t_status		status;
	__uint16_t		num_meals;
	int				is_full;
	t_data			*data;
}					t_philo;

/** error utils */
long				ft_atol(const char *str);
void				error_exit(const char *msg);
int					control_args(int argc);

/** philo utils */
int					init_data(int argc, char *argv[], t_data *data);

/** debugging */
void				print_data(t_data *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:55:30 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/30 17:09:58 by mgodawat         ###   ########.fr       */
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
# define DEBUG 1

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_global	t_global;

typedef enum e_time
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}						t_time;

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK_ONE,
	FORK_TWO,
	DIED,
}						t_status;

typedef struct s_fork
{
	pthread_mutex_t		mtx_fork;
	unsigned int		fork_id;
}						t_fork;

typedef struct s_philo
{
	unsigned int		philo_id;
	long				meals_count;
	bool				full;
	long				last_meal_time;
	t_fork				*right_fork;
	t_fork				*left_fork;
	pthread_t			thread_id;
	pthread_mutex_t		philo_mutex;
	t_global			*global_data;

}						t_philo;

typedef struct s_global
{
	unsigned int		nbr_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		must_eat_count;
	long				nbr_running_threads;
	long				start_simul;
	bool				end_simul;
	bool				all_threads_ready;
	pthread_mutex_t		mutex_data;
	pthread_mutex_t		mtx_print;
	t_fork				*forks;
	t_philo				*philos;
	pthread_t			thread_monitor;
}						t_global;

void					error_exit(const char *msg);
long					ft_atol(const char *str);
bool					control_args(int argc);
void					cleanup(t_global *data);
long					get_time(t_time timecode);
void					ft_usleep(long usec, t_global *data);
void					*safe_malloc(size_t bytes);
bool					set_bool(pthread_mutex_t *mutex_data, bool *dest,
							bool value);
bool					get_bool(pthread_mutex_t *mutex_data, bool *value);
bool					simulation_finished(t_global *data);
void					wait_all_threads(t_global *data);
void					join_threads(t_global *data);
void					simulation(t_global *data);
void					print_status(t_status status, t_philo *philo,
							bool debug);
void					set_long(pthread_mutex_t *mutex_data, long *dest,
							long value);
long					get_long(pthread_mutex_t *mutex_data, long *value);
void					set_increase_long(pthread_mutex_t *mutex, long *value);
void					monitoring(t_global *data);
bool					all_threads_are_running(pthread_mutex_t *mutex,
							long *threads, unsigned int nbr_of_philo);
void					handle_philo_one(t_global *data);
/** debugging functions */
void					print_data(t_global *data);
void					write_status_debug(t_status status, t_philo *philo,
							long elapsed_time);

#endif

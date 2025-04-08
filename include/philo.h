/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:55:30 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/07 19:39:16 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\x1b[38;2;251;73;52m"
# define GREEN "\x1b[38;2;184;187;38m"
# define YELLOW "\x1b[38;2;250;189;47m"
# define BLUE "\x1b[38;2;131;165;152m"
# define PURPLE "\x1b[38;2;211;134;155m"
# define CYAN "\x1b[38;2;142;192;124m"
# define PINK "\x1b[38;2;254;128;25m"
# define RESET "\x1b[0m"

# define PHILO_MAX 200
# define ER STDERR_FILENO
# define DEBUG 0

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK_ONE,
	FORK_TWO,
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
	__uint16_t		fulled_phils;
	struct timeval	simul_start;
	int				philo_died;
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

long				ft_atol(const char *str);
void				error_exit(const char *msg);
int					control_args(int argc);
void				philo_dies(t_data *data);
void				ft_usleep(__uint32_t time, t_data *data);
__uint32_t			elapsed_time(struct timeval *ref);
int					check_dead(t_data *data);
int					init_data(int argc, char *argv[], t_data *data);
void				init_mutexes(t_data *data, pthread_mutex_t *mtx_fork,
						pthread_mutex_t mtx[4]);
void				init_philo(t_philo *philo, int i, t_data *data);
void				print_message(t_philo *philo, t_status opcode, int fork_id);
void				thinking(t_philo *philo);
int					eat_with_fork_right(t_philo *philo);
int					eat_with_fork_left(t_philo *philo);
int					philo_one(t_philo *philo, __uint16_t fork_index);
void				sleeping(t_philo *philo);
int					check_starved_time(int id, t_data *data);
int					check_all_full(t_data *data);
void				destroy_mutex(t_data *data, pthread_mutex_t *mtx_fork,
						pthread_mutex_t mtx[4]);

/** debugging */
void				print_data(t_data *data);
void				write_status_debug(t_status status, t_philo *philo,
						__uint32_t elapsed_time, int fork_id);
void				debug_init_philo(t_philo *philo, t_data *data,
						__uint16_t i);

#endif

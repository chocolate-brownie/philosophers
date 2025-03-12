/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:55:30 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/12 05:10:58 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\x1b[38;2;255;179;186m"
# define GREEN "\x1b[38;2;186;255;201m"
# define YELLOW "\x1b[38;2;255;255;186m"
# define BLUE "\x1b[38;2;186;225;255m"
# define PURPLE "\x1b[38;2;223;186;255m"
# define CYAN "\x1b[38;2;186;255;255m"
# define PINK "\x1b[38;2;255;186;255m"
# define RESET "\x1b[0m"

# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef enum e_opcode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETATCH,
}				t_opcode;

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK,
	DIED,
}				t_status;

typedef struct s_data
{
	unsigned int nbr_of_philo;   // ok
	uint32_t time_to_die;        // ok
	uint32_t time_to_eat;        // ok
	uint32_t time_to_sleep;      // ok
	unsigned int must_eat_count; // ok

	struct timeval simul_start; // NOTE: first declation @start_simulation

	bool someone_dead; // ok

	pthread_mutex_t mtx_death;  // ok
	pthread_mutex_t mtx_print;  // ok
	pthread_mutex_t mtx_meal;   // ok
	pthread_mutex_t *mtx_forks; // ok
	struct s_philo *philos;     // NOTE: first declaration @init_philo
}				t_data;

typedef struct s_philo
{
	t_data *data;             // ok
	unsigned int philo_id;    // ok
	unsigned int meals_eaten; // ok

	struct timeval last_meal;    // NOTE: declared @eating
	pthread_mutex_t *fork_left;  // ok
	pthread_mutex_t *fork_right; // ok

	pthread_t philo_thread; // NOTE: first declaration @start_simulation
	t_status status;        // NOTE: first declaration @start_routine
}				t_philo;

/* utility stuff */
void			error_exit(const char *error_msg);
void			*safe_malloc(size_t size);
uint32_t		get_elapsed_time(struct timeval start);
struct timeval	get_current_time(struct timeval *time);
int				ft_usleep(uint32_t milliseconds);
void			cleanup(t_philo **philos, t_data *data);
void			*ft_memset(void *s, int c, size_t n);

/* debuggin stuff */
void			print_message(t_philo *philo, t_status status);
void			print_validated_data(t_data *data);
void			print_box_message(const char *msg);
void			print_final_state(t_data *data);
uint64_t		print_relative_ms(struct timeval time, struct timeval start);
void			print_philo_data(t_philo *philo, unsigned int i);

/* other stuff */
void			handle_mutexes(pthread_mutex_t *mutex, t_opcode opcode);
void			handle_threads(pthread_t *thread,
					void *(*function_name)(void *), void *arg, t_opcode opcode);
void			start_simulation(t_data *data);

/* routine stuff */
void			*start_routine(void *arg);
bool			check_meals_complete(t_philo *philo);
void			*death_checker(void *arg);

#endif

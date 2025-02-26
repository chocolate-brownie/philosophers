/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:25:09 by mgodawat          #+#    #+#             */
/*   Updated: 2025/02/26 23:00:43 by mgodawat         ###   ########.fr       */
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

enum				t_opcode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK
};

typedef struct s_data
{
	unsigned int nbr_of_philo;   // ok
	uint32_t time_to_die;        // ok
	uint32_t time_to_eat;        // ok
	uint32_t time_to_sleep;      // ok
	unsigned int must_eat_count; // ok

	struct timeval simul_start; // simul has to start during the routine

	bool someone_dead; // ok

	pthread_mutex_t	*mtx_death;
	pthread_mutex_t	*mtx_print;
	pthread_mutex_t	*mtx_meal;
	pthread_mutex_t	*mtx_forks;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	t_data			*data;
	unsigned int	philo_id;
	unsigned int	meals_eaten;
	bool			philo_is_full;
	uint32_t		last_meal;
	unsigned int	fork_left;
	unsigned int	fork_right;

}					t_philo;

void				print_validated_data(t_philo *philo);
void				error_exit(const char *error_msg);

void				create_mutex(pthread_mutex_t *mutex, enum t_opcode opcode);

#endif

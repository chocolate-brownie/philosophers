/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:55:30 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/25 17:53:30 by mgodawat         ###   ########.fr       */
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
# include <sys/time.h> # include <unistd.h>

# define RED "\x1b[38;2;255;179;186m"
# define GREEN "\x1b[38;2;186;255;201m"
# define YELLOW "\x1b[38;2;255;255;186m"
# define BLUE "\x1b[38;2;186;225;255m"
# define PURPLE "\x1b[38;2;223;186;255m"
# define CYAN "\x1b[38;2;186;255;255m"
# define PINK "\x1b[38;2;255;186;255m"
# define RESET "\x1b[0m"

# define PHILO_MAX 200

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_global	t_global;

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK,
	DIED,
}						t_status;

/**NOTE:
 * end_simul triggers if a philo dies or all philos are full
 * */

typedef struct s_fork
{
	pthread_mutex_t		*mtx_fork;
	unsigned int		fork_id;
}						t_fork;

typedef struct s_philo
{
	unsigned int		philo_id;
	unsigned int		meals_count;
	bool				full;
	struct timeval		*last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_global			*global_data;

}						t_philo;

typedef struct s_global
{
	unsigned int		nbr_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		must_eat_count;
	struct timeval		*start_simul;
	bool				end_simul;
	t_fork				*forks;
	t_philo				*philos;
}						t_global;

/** utils */
void					error_exit(const char *msg);
long					ft_atol(const char *str);
bool					control_args(int argc);

/** wrappers */
void					*safe_malloc(size_t bytes);
#endif

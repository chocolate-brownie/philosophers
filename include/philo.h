/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:55:30 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/21 20:06:45 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
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

# ifdef DEBUG
#  define DEBUG_PRINT(...) printf("DEBUG: "__VA_ARGS__)
#  define DEBUG_PRINT_RED(...) printf(RED "DEBUG: " RESET __VA_ARGS__)
#  define DEBUG_PRINT_GREEN(...) printf(GREEN "DEBUG: " RESET __VA_ARGS__)
#  define DEBUG_PRINT_YELLOW(...) printf(YELLOW "DEBUG: " RESET __VA_ARGS__)
#  define DEBUG_PRINT_BLUE(...) printf(BLUE "DEBUG: " RESET __VA_ARGS__)
#  define DEBUG_PRINT_PURPLE(...) printf(PURPLE "DEBUG: " RESET __VA_ARGS__)
#  define DEBUG_PRINT_CYAN(...) printf(CYAN "DEBUG: " RESET __VA_ARGS__)
# else
#  define DEBUG_PRINT(...) ((void)0)
#  define DEBUG_PRINT_RED(...) ((void)0)
#  define DEBUG_PRINT_GREEN(...) ((void)0)
#  define DEBUG_PRINT_YELLOW(...) ((void)0)
#  define DEBUG_PRINT_BLUE(...) ((void)0)
#  define DEBUG_PRINT_PURPLE(...) ((void)0)
#  define DEBUG_PRINT_CYAN(...) ((void)0)
# endif

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
}					t_opcode;

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK,
	DIED,
}					t_status;

typedef struct s_data
{
	unsigned int	nbr_of_philo;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		time_to_think;
	unsigned int	must_eat_count;
	struct timeval	simul_start;
	bool			someone_dead;
	unsigned int	fulled_phils;
	struct timeval	*last_meal;
	pthread_mutex_t	*mtx_death;
	pthread_mutex_t	*mtx_print;
	pthread_mutex_t	*mtx_meal;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	*mtx_full;
}					t_data;

typedef struct s_philo
{
	unsigned int	philo_id;
	t_status		status;
	t_data			*data;
	unsigned int	meals_eaten;
	bool			is_full;
}					t_philo;

/** main functions */
void				check_input(int argc, char *argv[]);

/** libft functions */
unsigned int		ft_strlen(const char *str);

/** utillity functions */
void				error_exit(const char *err_msg);
void				*safe_malloc(size_t size);
void				handle_mutexes(pthread_mutex_t *mutex, t_opcode opcode);
void				handle_threads(pthread_t *thread,
						void *(*function_name)(void *), void *arg,
						t_opcode opcode);
void				cleanup(t_data *data, pthread_t *threads,
						pthread_mutex_t *mtxes);

/** routine functions */
void				*philo_routine(void *arg);
void				*monitor_routine(void *arg);
void				philo_mark_dead(t_data *data);
bool				check_death(t_data *data);
void				print_message(t_philo *philo, t_status status);

/** fork grabbing mecha */
bool	grabbing_forks(t_philo *philo);


/** time utility functions */
void				ft_usleep(uint32_t time, t_data *data);
struct timeval		get_current_time(struct timeval *time);
uint32_t			get_elapsed_time(struct timeval start);

/** debug functions
 * (WARNING: delete the debug.c files before pusing it has norminette error)
 */
void				print_validated_data(t_data *data);

#endif

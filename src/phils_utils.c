/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:31:20 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 13:56:53 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(int argc, char *argv[], t_data *data)
{
	data->nbr_of_phils = ft_atol(argv[1]);
	if (data->nbr_of_phils > PHILO_MAX)
		return (write(ER, "[Error]: PHILO_MAX\n", 19), 1);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->time_to_think = 0;
	if (data->time_to_sleep <= data->time_to_eat)
		data->time_to_think = 2 * data->time_to_eat - data->time_to_sleep;
	data->must_eat_times = 0;
	if (argc == 6)
		data->must_eat_times = ft_atol(argv[5]);
	gettimeofday(&data->simul_start, NULL);
	data->philo_died = 0;
	data->fulled_phils = 0;
	data->last_meal = malloc(sizeof(struct timeval) * data->nbr_of_phils);
	if (!data->last_meal)
		return (1);
	data->mtx_fork = NULL;
	data->mtx_full = NULL;
	data->mtx_dead = NULL;
	data->mtx_meal = NULL;
	data->mtx_print = NULL;
	return (0);
}

void	init_mutexes(t_data *data, pthread_mutex_t *mtx_fork,
		pthread_mutex_t mtx[4])
{
	__uint16_t	i;

	i = -1;
	while (++i < data->nbr_of_phils)
		pthread_mutex_init(&mtx_fork[i], NULL);
	pthread_mutex_init(&mtx[FULL], NULL);
	pthread_mutex_init(&mtx[DEAD], NULL);
	pthread_mutex_init(&mtx[MEAL], NULL);
	pthread_mutex_init(&mtx[PRINT], NULL);
	data->mtx_fork = mtx_fork;
	data->mtx_full = &mtx[FULL];
	data->mtx_dead = &mtx[DEAD];
	data->mtx_meal = &mtx[MEAL];
	data->mtx_print = &mtx[PRINT];
}

void	init_philo(t_philo *philo, int i, t_data *data)
{
	philo->id = i + 1;
	philo->status = EATING;
	data->last_meal[i] = data->simul_start;
	philo->num_meals = 0;
	philo->is_full = 0;
	philo->data = data;
	if (DEBUG == 1)
		debug_init_philo(philo, data, i);
}

void	destroy_mutex(t_data *data, pthread_mutex_t *mtx_fork,
		pthread_mutex_t mtx[4])
{
	__uint16_t	i;

	i = -1;
	while (++i < data->nbr_of_phils)
		pthread_mutex_destroy(&mtx_fork[i]);
	pthread_mutex_destroy(&mtx[FULL]);
	pthread_mutex_destroy(&mtx[DEAD]);
	pthread_mutex_destroy(&mtx[MEAL]);
	pthread_mutex_destroy(&mtx[PRINT]);
	free(mtx_fork);
}

void	print_message(t_data *data, int id, t_status action)
{
	pthread_mutex_lock(data->mtx_print);
	if (check_sb_dead(data) && action != DIED)
	{
		pthread_mutex_unlock(data->mtx_print);
		return ;
	}
	if (action == THINKING)
		printf(YELLOW "%05u %2d is thinking\n" RESET,
			elapsed_time(&data->simul_start), id);
	else if (action == EATING)
		printf(PINK "%05u %2d is eating\n" RESET,
			elapsed_time(&data->simul_start), id);
	else if (action == SLEEPING)
		printf(BLUE "%05u %2d is sleeping\n" RESET,
			elapsed_time(&data->simul_start), id);
	else if (action == FORK_ONE || action == FORK_TWO)
		printf("%05u %2d has taken a fork\n", elapsed_time(&data->simul_start),
			id);
	else if (action == DIED)
		printf(RED "%05u %2d died\n" RESET, elapsed_time(&data->simul_start),
			id);
	pthread_mutex_unlock(data->mtx_print);
}

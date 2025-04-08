/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:31:20 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/07 19:49:12 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(int argc, char *argv[], t_data *data)
{
	if ((data->nbr_of_phils = ft_atol(argv[1])) >= PHILO_MAX)
		return (write(ER, "Philo Max is 200\n", 17), 1);
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
	__uint8_t	i;

	i = -1;
	while (++i < data->nbr_of_phils)
		pthread_mutex_init(&mtx_fork[i], NULL);
	pthread_mutex_init(mtx + FULL, NULL);
	pthread_mutex_init(mtx + DEAD, NULL);
	pthread_mutex_init(mtx + MEAL, NULL);
	pthread_mutex_init(mtx + PRINT, NULL);
	data->mtx_fork = mtx_fork;
	data->mtx_full = mtx + FULL;
	data->mtx_dead = mtx + DEAD;
	data->mtx_meal = mtx + MEAL;
	data->mtx_print = mtx + PRINT;
}

void	init_philo(t_philo *philo, int i, t_data *data)
{
	philo->id = i + 1;
	philo->status = EATING;
	data->last_meal[i] = data->simul_start;
	philo->num_meals = 0;
	philo->is_full = 0;
	philo->data = data;
	if (DEBUG == 2)
		debug_init_philo(philo, data, i);
}

int	check_dead(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->mtx_dead);
	if (data->philo_died)
		i = 1;
	pthread_mutex_unlock(data->mtx_dead);
	return (i);
}

void	print_message(t_philo *philo, t_status opcode, int fork_id)
{
	__uint32_t	elapsed;
	t_data		*data;

	data = philo->data;
	pthread_mutex_lock(data->mtx_print);
	elapsed = elapsed_time(&data->simul_start);
	if (DEBUG == 1 || DEBUG == 2)
		write_status_debug(opcode, philo, elapsed, fork_id);
	else
	{
		if (opcode == FORK_ONE || opcode == FORK_TWO)
			printf("%05u %d has taken a fork\n", elapsed, philo->id);
		else if (opcode == EATING)
			printf("%05u %d eating\n", elapsed, philo->id);
		else if (opcode == THINKING)
			printf("%05u %d thinking\n", elapsed, philo->id);
		else if (opcode == SLEEPING)
			printf("%05u %d sleeping\n", elapsed, philo->id);
		else if (opcode == DIED)
			printf(RED "%05u %d died\n" RESET, elapsed, philo->id);
	}
	pthread_mutex_unlock(data->mtx_print);
}

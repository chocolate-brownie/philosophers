/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:00:56 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/30 16:39:46 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>

void	wait_all_threads(t_global *data)
{
	while (!get_bool(&data->mutex_data, &data->all_threads_ready))
		;
}

void	print_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECONDS) - philo->global_data->start_simul;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	pthread_mutex_lock(&philo->global_data->mtx_print);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == FORK_ONE || status == FORK_TWO)
			&& (!simulation_finished(philo->global_data)))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->philo_id);
		else if (status == EATING && (!simulation_finished(philo->global_data)))
			printf("%-6ld %d is eating\n", elapsed, philo->philo_id);
		else if (status == THINKING
			&& (!simulation_finished(philo->global_data)))
			printf("%-6ld %d is thinking\n", elapsed, philo->philo_id);
		else if (status == SLEEPING
			&& (!simulation_finished(philo->global_data)))
			printf("%-6ld %d is sleeping\n", elapsed, philo->philo_id);
		else if (status == DIED)
			printf(RED "%-6ld %d died\n" RESET, elapsed, philo->philo_id);
	}
	pthread_mutex_unlock(&philo->global_data->mtx_print);
}

void	join_threads(t_global *data)
{
	unsigned int	i;
	int				err;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		err = pthread_join(data->philos[i].thread_id, NULL);
		if (err)
			write(STDERR_FILENO, "error join threads\n", 19);
	}
}

void	set_increase_long(pthread_mutex_t *mutex, long *value)
{
	int	err_mtx;

	err_mtx = pthread_mutex_lock(mutex);
	if (err_mtx != 0)
		error_exit("locking mutex");
	(*value)++;
	err_mtx = pthread_mutex_unlock(mutex);
	if (err_mtx != 0)
		error_exit("unlocking mutex");
}

bool	all_threads_are_running(pthread_mutex_t *mutex, long *threads,
		unsigned int nbr_of_philo)
{
	int		err_mtx;
	bool	result;

	result = false;
	err_mtx = pthread_mutex_lock(mutex);
	if (err_mtx != 0)
	{
		write(STDERR_FILENO, "Error locking mutex\n", 20);
		return (false);
	}
	if (*threads == (long)nbr_of_philo)
		result = true;
	err_mtx = pthread_mutex_unlock(mutex);
	if (err_mtx != 0)
	{
		write(STDERR_FILENO, "Error unlocking mutex\n", 22);
		return (false);
	}
	return (result);
}

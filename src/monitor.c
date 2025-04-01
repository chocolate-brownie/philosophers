/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:48 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/01 15:00:50 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (true);
	elapsed = get_time(MILLISECONDS) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = (long)philo->global_data->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}
*/
static void	*monitor_routine(void *arg)
{
	t_global	*data;

	data = (t_global *)arg;
	/* printf("Monitor data structure at %p\n", (void *)data);
	printf("Monitor mutex_data at %p\n", (void *)&data->mutex_data);
	printf("Monitor nbr_running_threads at %p (value: %ld)\n",
		(void *)&data->nbr_running_threads, data->nbr_running_threads); */
	// Make sure all philos are running
	while (!all_threads_are_running(&data->mutex_data,
			&data->nbr_running_threads, data->nbr_of_philo))
		ft_usleep(1000, data);
	return (NULL);
}

void	monitoring(t_global *data)
{
	int	err_thread;

	err_thread = pthread_create(&data->thread_monitor, NULL, &monitor_routine,
			data);
	if (err_thread != 0)
	{
		write(STDERR_FILENO, "Error creatin monitor threads\n", 30);
		return ;
	}
	// pthread_join(data->thread_monitor, NULL);
}

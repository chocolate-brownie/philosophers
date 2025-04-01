/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:48 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/01 21:26:21 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	philo_died(t_philo *philo)
{
	long	current_time;
	long	last_meal_time;
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	current_time = get_time(MILLISECONDS);
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = current_time - last_meal_time;
	time_to_die = (long)philo->global_data->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

static void	*monitor_routine(void *arg)
{
	t_global		*data;
	unsigned int	i;

	data = (t_global *)arg;
	while (!all_threads_are_running(&data->mutex_data,
			&data->nbr_running_threads, data->nbr_of_philo))
		ft_usleep(1000, data);
	while (!simulation_finished(data))
	{
		i = -1;
		while (++i < data->nbr_of_philo && !simulation_finished(data))
		{
			if (philo_died(&data->philos[i]))
			{
				set_bool(&data->mutex_data, &data->end_simul, true);
				print_status(DIED, &data->philos[i], DEBUG);
			}
		}
		usleep(1e3);
	}
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:08:00 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/01 19:05:47 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*handle_philo_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->global_data);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	set_increase_long(&philo->global_data->mutex_data,
		&philo->global_data->nbr_running_threads);
	print_status(FORK_ONE, philo, DEBUG);
	while (!simulation_finished(philo->global_data))
		usleep(200);
	return (NULL);
}

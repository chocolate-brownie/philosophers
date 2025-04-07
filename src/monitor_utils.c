/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:56:34 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/07 02:21:28 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_starved_time(t_data *data, __uint16_t id)
{
	int			is_starved;
	__uint32_t	elapsed;
	__uint32_t	last_meal_time;

	is_starved = 0;
	pthread_mutex_lock(data->mtx_meal);
	last_meal_time = elapsed_time(&data->last_meal[id]);
	if (last_meal_time > data->time_to_die)
		is_starved = 1;
	pthread_mutex_unlock(data->mtx_meal);
	if (is_starved == 1)
	{
		pthread_mutex_lock(data->mtx_print);
		elapsed = elapsed_time(&data->simul_start);
		if (DEBUG == 1 || DEBUG == 0)
			printf(RED "%05u %d died\n" RESET, elapsed, id + 1);
	}
	return (is_starved);
}

int	check_all_full(t_data *data)
{
	int	result;

	result = 0;
	pthread_mutex_lock(data->mtx_full);
	if (data->fulled_phils == data->nbr_of_phils)
		result = 1;
	pthread_mutex_unlock(data->mtx_full);
	return (result);
}

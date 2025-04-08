/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:56:34 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/07 19:19:49 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_starved_time(int id, t_data *data)
{
	int			i;
	__uint32_t	elapsed;

	i = 0;
	pthread_mutex_lock(data->mtx_meal);
	if (elapsed_time(data->last_meal + id) > data->time_to_die)
		i = 1;
	pthread_mutex_unlock(data->mtx_meal);
	if (i == 1)
	{
		pthread_mutex_lock(data->mtx_print);
		elapsed = elapsed_time(&data->simul_start);
		if (DEBUG == 1 || DEBUG == 0 || DEBUG == 2)
			printf(RED "%05u %d died\n" RESET, elapsed, id + 1);
		pthread_mutex_unlock(data->mtx_print);
	}
	return (i);
}

int	check_all_full(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->mtx_full);
	if (data->fulled_phils == data->nbr_of_phils)
		i = 1;
	pthread_mutex_unlock(data->mtx_full);
	return (i);
}

void	destroy_mutex(t_data *data, pthread_mutex_t *mtx_fork,
		pthread_mutex_t mtx[4])
{
	__uint16_t	i;

	i = -1;
	while (++i < data->nbr_of_phils)
		pthread_mutex_destroy(&mtx_fork[i]);
	pthread_mutex_destroy(mtx + FULL);
	pthread_mutex_destroy(mtx + DEAD);
	pthread_mutex_destroy(mtx + MEAL);
	pthread_mutex_destroy(mtx + PRINT);
	free(mtx_fork);
}

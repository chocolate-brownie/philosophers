/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:53:33 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/07 20:23:43 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_usleep(uint32_t milliseconds)
{
	struct timeval	start;
	uint32_t		elapsed;

	get_current_time(&start);
	while (1)
	{
		elapsed = get_elapsed_time(start);
		if (elapsed >= milliseconds)
			break ;
		usleep(500);
	}
	return (0);
}

bool	check_meals_complete(t_philo *philo)
{
	if (philo->data->must_eat_count == 0)
		return (false);
	return (philo->meals_eaten >= philo->data->must_eat_count);
}

uint32_t	get_time_last_meal(t_data *data, unsigned int i)
{
	uint32_t	time_since_meal;

	handle_mutexes(&data->mtx_meal, LOCK);
	time_since_meal = get_elapsed_time(data->philos[i].last_meal);
	handle_mutexes(&data->mtx_meal, UNLOCK);
	return (time_since_meal);
}

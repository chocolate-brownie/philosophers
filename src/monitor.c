/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:23:05 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/08 01:58:50 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_philosopher_death(t_data *data, unsigned int i)
{
	uint32_t	time_since_meal;

	time_since_meal = get_time_last_meal(data, i);
	if (time_since_meal >= data->time_to_die)
	{
		handle_mutexes(&data->mtx_death, LOCK);
		if (!data->someone_dead)
		{
			data->someone_dead = true;
			print_message(&data->philos[i], DIED);
		}
		handle_mutexes(&data->mtx_death, UNLOCK);
		return (true);
	}
	return (false);
}

static bool	check_all_philosophers_ate(t_data *data)
{
	unsigned int	i;
	bool			all_ate_enough;

	if (data->must_eat_count == 0)
		return (false);
	i = -1;
	all_ate_enough = true;
	while (++i < data->nbr_of_philo)
	{
		if (!check_meals_complete(&data->philos[i]))
		{
			all_ate_enough = false;
			break ;
		}
	}
	return (all_ate_enough);
}

void	*death_checker(void *arg)
{
	t_data			*data;
	unsigned int	i;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		handle_mutexes(&data->mtx_death, LOCK);
		if (data->someone_dead)
		{
			handle_mutexes(&data->mtx_death, UNLOCK);
			return (NULL);
		}
		handle_mutexes(&data->mtx_death, UNLOCK);
		i = -1;
		while (++i < data->nbr_of_philo)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
		}
		if (check_all_philosophers_ate(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

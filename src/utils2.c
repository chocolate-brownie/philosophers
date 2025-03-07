/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:53:33 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/07 03:39:39 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <cstdlib>
#include <stdbool.h>

struct timeval	get_current_time(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		error_exit("gettimeofday failed");
	return (*time);
}

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

/*if the time since last_meal exceeds the time_to_die the philo has dead*/
static bool	is_philo_dead(t_philo *philo)
{
	uint32_t	time_since_last_meal;

	handle_mutexes(&philo->data->mtx_meal, LOCK);
	time_since_last_meal = get_elapsed_time(philo->last_meal);
	handle_mutexes(&philo->data->mtx_meal, UNLOCK);
	return (time_since_last_meal >= philo->data->time_to_die);
}

/*
 * I want to go up to each philo and ask are you dead?
 * but the questioning should happen as long as the original program is alive
 * if someone is dead lock the mutex safely and update that someone died
 * print the death message in RED
 * exit the thread
 * */
void	*death_checker(void *arg)
{
	t_data			*data;
	unsigned int	i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->nbr_of_philo)
	{
		if (is_philo_dead(&data->philos[i]))
		{
			handle_mutexes(&data->mtx_death, LOCK);
			data->someone_dead = true;
			handle_mutexes(&data->mtx_death, UNLOCK);
			print_message(data->philos, DIED);
			return (NULL);
		}
	}
	ft_usleep(1000);
	return (NULL);
}

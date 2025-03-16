/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:53:33 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/14 12:08:29 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_death(t_philo *philo)
{
	bool		is_dead;
	uint32_t	time_since_last_meal;

	is_dead = false;
	handle_mutexes(&philo->data->mtx_death, LOCK);
	if (philo->data->someone_dead == true)
	{
		handle_mutexes(&philo->data->mtx_death, UNLOCK);
		return (true);
	}
	handle_mutexes(&philo->data->mtx_meal, LOCK);
	time_since_last_meal = get_elapsed_time(philo->last_meal);
	if (time_since_last_meal >= philo->data->time_to_die)
	{
		philo->data->someone_dead = true;
		print_message(philo, DIED);
		is_dead = true;
	}
	handle_mutexes(&philo->data->mtx_meal, UNLOCK);
	handle_mutexes(&philo->data->mtx_death, UNLOCK);
	return (is_dead);
}

int	ft_usleep(uint32_t milliseconds, t_philo *philo)
{
	struct timeval	start;
	uint32_t		elapsed;

	get_current_time(&start);
	while (1)
	{
		if (check_death(philo))
			return (1);
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

void	cleanup(t_philo **philos, t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		handle_mutexes(&data->mtx_forks[i], DESTROY);
		i++;
	}
	handle_mutexes(&data->mtx_death, DESTROY);
	handle_mutexes(&data->mtx_print, DESTROY);
	handle_mutexes(&data->mtx_meal, DESTROY);
	if (data->mtx_forks)
		free(data->mtx_forks);
	if (*philos)
	{
		free(*philos);
		*philos = NULL;
	}
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = (unsigned char)c;
	return (s);
}

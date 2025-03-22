/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:47:00 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/22 12:03:12 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	take_forks(t_philo *philo, unsigned int fork_index)
{
	handle_mutexes(&philo->data->mtx_forks[fork_index], LOCK);
	if (check_death(philo->data))
	{
		handle_mutexes(&philo->data->mtx_forks[fork_index], UNLOCK);
		return (false);
	}
	print_message(philo, FORK);
	return (true);
}

void	get_fork_indices(t_philo *philo, unsigned int *left_fork,
		unsigned int *right_fork)
{
	*left_fork = philo->philo_id - 1;
	*right_fork = philo->philo_id % philo->data->nbr_of_philo;
}

static bool	single_philo_fork(t_philo *philo, unsigned int *fork_index)
{
	bool	success;

	if (philo->data->nbr_of_philo == 1)
	{
		if (!take_forks(philo, *fork_index))
			return (false);
		ft_usleep(philo->data->time_to_die + 10, philo->data);
		handle_mutexes(&philo->data->mtx_forks[*fork_index], UNLOCK);
		return (false);
	}
	return (true);
}

static bool	multiple_philo_fork(t_philo *philo, unsigned int *left_fork,
		unsigned int *right_fork)
{
	if (philo->philo_id % 2)
	{
		if (!take_forks(philo, *left_fork))
			return (false);
		if (!take_forks(philo, *right_fork))
		{
			handle_mutexes(&philo->data->mtx_forks[*left_fork], UNLOCK);
			return (false);
		}
	}
	else
	{
		if (!take_forks(philo, *right_fork))
			return (false);
		if (!take_forks(philo, *left_fork))
		{
			handle_mutexes(&philo->data->mtx_forks[*right_fork], UNLOCK);
			return (false);
		}
	}
	return (true);
}

bool	grabbing_forks(t_philo *philo)
{
	unsigned int	left_fork;
	unsigned int	right_fork;

	get_fork_indices(philo, &left_fork, &right_fork);
	if (philo->data->nbr_of_philo == 1)
		return (single_philo_fork(philo, &left_fork));
	return (multiple_philo_fork(philo, &left_fork, &right_fork));
}

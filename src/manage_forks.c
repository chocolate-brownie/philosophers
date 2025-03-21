/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:47:00 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/21 20:30:56 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	take_forks(t_philo *philo, unsigned int fork_index)
{
}

static void	get_fork_indices(t_philo *philo, unsigned int *left_fork,
		unsigned int *right_fork)
{
	*left_fork = philo->philo_id - 1;
	*right_fork = philo->philo_id % philo->data->nbr_of_philo;
}

static void	handle_philo_one(t_philo *philo, unsigned int fork_index)
{
	if (philo->data->nbr_of_philo == 1)
	{
		if (!take_forks(philo, fork_index))
			return ;
		ft_usleep(philo->data->time_to_die + 10, philo->data);
		handle_mutexes(&philo->data->mtx_forks[fork_index], UNLOCK);
	}
}

bool	grabbing_forks(t_philo *philo)
{
	unsigned int	left_fork;
	unsigned int	right_fork;

	get_fork_indices(philo, &left_fork, &right_fork);
	if (philo->philo_id % 2)
	{
		if (!take_forks(philo, left_fork))
			return (false);
		if (!take_forks(philo, right_fork))
		{
			handle_mutexes(&philo->data->mtx_forks[left_fork], UNLOCK);
			return (false);
		}
	}
	else
	{
		if (!take_forks(philo, right_fork))
			return (false);
		if (!take_forks(philo, left_fork))
		{
			handle_mutexes(&philo->data->mtx_forks[right_fork], UNLOCK);
			return (false);
		}
	}
	return (true);
}

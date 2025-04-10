/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:23:20 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 12:06:35 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	sleeping(t_philo *philo)
{
	int	i;

	i = philo->id;
	print_message(philo->data, i, SLEEPING);
	ft_usleep(philo->data->time_to_sleep, philo->data);
	philo->status = THINKING;
}

void	thinking(t_philo *philo)
{
	print_message(philo->data, philo->id, THINKING);
	if (philo->data->nbr_of_phils % 2)
		ft_usleep(philo->data->time_to_think, philo->data);
	philo->status = EATING;
}

static void	eating(t_philo *philo)
{
	if (check_sb_dead(philo->data))
		return ;
	print_message(philo->data, philo->id, EATING);
	pthread_mutex_lock(philo->data->mtx_meal);
	gettimeofday(&philo->data->last_meal[philo->id - 1], NULL);
	pthread_mutex_unlock(philo->data->mtx_meal);
	philo->num_meals += 1;
	if (philo->data->must_eat_times && !philo->is_full)
	{
		if (philo->num_meals == philo->data->must_eat_times)
		{
			pthread_mutex_lock(philo->data->mtx_full);
			philo->data->fulled_phils += 1;
			pthread_mutex_unlock(philo->data->mtx_full);
			philo->is_full = 1;
		}
	}
	ft_usleep(philo->data->time_to_eat, philo->data);
}

int	eat_with_fork_left(t_philo *philo)
{
	__uint16_t	left_fork;
	__uint16_t	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->nbr_of_phils;
	pthread_mutex_lock(&philo->data->mtx_fork[left_fork]);
	if (check_sb_dead(philo->data))
		return (pthread_mutex_unlock(&philo->data->mtx_fork[left_fork]), 1);
	print_message(philo->data, philo->id, FORK_TWO);
	if (philo_one(philo, left_fork) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->mtx_fork[right_fork]);
	if (check_sb_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mtx_fork[left_fork]);
		pthread_mutex_unlock(&philo->data->mtx_fork[right_fork]);
		return (1);
	}
	print_message(philo->data, philo->id, FORK_ONE);
	eating(philo);
	pthread_mutex_unlock(&philo->data->mtx_fork[left_fork]);
	pthread_mutex_unlock(&philo->data->mtx_fork[right_fork]);
	return (0);
}

int	eat_with_fork_right(t_philo *philo)
{
	__uint16_t	left_fork;
	__uint16_t	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->nbr_of_phils;
	pthread_mutex_lock(&philo->data->mtx_fork[right_fork]);
	if (check_sb_dead(philo->data))
		return (pthread_mutex_unlock(&philo->data->mtx_fork[right_fork]), 1);
	print_message(philo->data, philo->id, FORK_ONE);
	pthread_mutex_lock(&philo->data->mtx_fork[left_fork]);
	if (check_sb_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mtx_fork[right_fork]);
		pthread_mutex_unlock(&philo->data->mtx_fork[left_fork]);
		return (1);
	}
	print_message(philo->data, philo->id, FORK_TWO);
	eating(philo);
	pthread_mutex_unlock(&philo->data->mtx_fork[right_fork]);
	pthread_mutex_unlock(&philo->data->mtx_fork[left_fork]);
	return (0);
}

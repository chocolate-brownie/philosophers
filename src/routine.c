/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:36:00 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/08 03:57:36 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	sleeping(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_message(philo, SLEEPING);
	ft_usleep(data->time_to_sleep);
	philo->status = THINKING;
}

static void	grabbing_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->data->nbr_of_philo % 2)
	{
		handle_mutexes(&data->mtx_forks[philo->fork_right], LOCK);
		print_message(philo, FORK);
		handle_mutexes(&data->mtx_forks[philo->fork_left], LOCK);
		print_message(philo, FORK);
	}
	else
	{
		handle_mutexes(&data->mtx_forks[philo->fork_left], LOCK);
		print_message(philo, FORK);
		handle_mutexes(&data->mtx_forks[philo->fork_right], LOCK);
		print_message(philo, FORK);
	}
}

static void	thinking(t_philo *philo)
{
	print_message(philo, THINKING);
	philo->status = EATING;
}

static void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	grabbing_forks(philo);
	// update the last meal time and meals eaten count
	handle_mutexes(&data->mtx_meal, LOCK);
	get_current_time(&philo->last_meal);
	philo->meals_eaten++;
	handle_mutexes(&data->mtx_meal, UNLOCK);
	// print the message
	print_message(philo, EATING);
	ft_usleep(data->time_to_eat);
	// unlock the forks from grabbing_forks
	if (data->nbr_of_philo % 2)
	{
		handle_mutexes(&data->mtx_forks[philo->fork_right], UNLOCK);
		handle_mutexes(&data->mtx_forks[philo->fork_left], UNLOCK);
	}
	else
	{
		handle_mutexes(&data->mtx_forks[philo->fork_left], UNLOCK);
		handle_mutexes(&data->mtx_forks[philo->fork_right], UNLOCK);
	}
	philo->status = SLEEPING;
}

/**
 * simulation should stop if someone died or the number of meals have eaten
 * add a delay to the even philosophers to reduce deadlock chance
 *
 * should be something like while (!check_meals_complete && !philo_dead)
 */

void	*start_routine(void *arg)
{
	t_philo	*philo;
	bool	someone_dead;

	philo = (t_philo *)arg;
	philo->status = THINKING;
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (1)
	{
		handle_mutexes(&philo->data->mtx_death, LOCK);
		someone_dead = philo->data->someone_dead;
		handle_mutexes(&philo->data->mtx_death, UNLOCK);
		if (someone_dead || check_meals_complete(philo))
			break ;
		if (philo->status == THINKING)
			thinking(philo);
		else if (philo->status == EATING)
			eating(philo);
		else if (philo->status == SLEEPING)
			sleeping(philo);
	}
	return (NULL);
}

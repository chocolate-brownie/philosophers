/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:29:02 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/16 03:28:35 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eating(t_philo *philo)
{
	grabbing_forks(philo, LOCK);
	handle_mutexes(&philo->data->mtx_meal, LOCK);
	get_current_time(&philo->last_meal);
	handle_mutexes(&philo->data->mtx_meal, UNLOCK);
	print_message(philo, EATING);
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat, philo);
	grabbing_forks(philo, UNLOCK);
	philo->status = SLEEPING;
}

static void	sleeping(t_philo *philo)
{
	if (philo->status == SLEEPING)
	{
		print_message(philo, SLEEPING);
		ft_usleep(philo->data->time_to_sleep, philo);
	}
	philo->status = THINKING;
}

static void	thinking(t_philo *philo)
{
	if (philo->status == THINKING)
	{
		print_message(philo, THINKING);
		ft_usleep(500, philo);
	}
	philo->status = EATING;
}

static void	execute_philo_cycle(t_philo *philo)
{
	if (philo->status == EATING)
	{
		eating(philo);
		return ;
	}
	if (philo->status == SLEEPING)
	{
		sleeping(philo);
		return ;
	}
	if (philo->status == THINKING)
	{
		thinking(philo);
		return ;
	}
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	get_current_time(&philo->last_meal);
	if (philo->data->nbr_of_philo == 1)
	{
		handle_one_philo(philo);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo);
	while (!check_death(philo) && !check_meals_complete(philo))
		execute_philo_cycle(philo);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:29:02 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/12 05:27:48 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	grabbing_forks(t_philo *philo, t_opcode opcode)
{
	// HACK: print message function is locking the mtx_print
	if (philo->philo_id % 2 == 0)
	{
		handle_mutexes(philo->fork_left, opcode);
		print_message(philo, FORK);
		handle_mutexes(philo->fork_right, opcode);
		print_message(philo, FORK);
	}
	else
	{
		handle_mutexes(philo->fork_right, opcode);
		print_message(philo, FORK);
		handle_mutexes(philo->fork_left, opcode);
		print_message(philo, FORK);
	}
}

static void	eating(t_philo *philo)
{
	// grabbing forks
	grabbing_forks(philo, LOCK);
	// updating the last meal time
	handle_mutexes(&philo->data->mtx_meal, LOCK);
	get_current_time(&philo->data->philos->last_meal);
	handle_mutexes(&philo->data->mtx_meal, UNLOCK);
	// lock mutexes and print the eating
	print_message(philo, EATING);
	philo->meals_eaten++;
	// release forks
	grabbing_forks(philo, UNLOCK);
}

static void	sleeping(t_philo *philo)
{
	return ;
}

static void	thinking(t_philo *philo)
{
	return ;
}

void	*start_routine(t_philo *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("\n\nsomeone_dead: %s%s%s\n\n",
		philo->data->someone_dead ? RED : GREEN,
		philo->data->someone_dead ? "true" : "false", RESET);
	while (1)
	{
		eating(philo);
		/*sleeping(data);*/
		/*thinking(data);*/
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 03:05:09 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/16 03:22:27 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	handle_one_philo(t_philo *philo)
{
	handle_mutexes(philo->fork_left, LOCK);
	print_message(philo, FORK);
	ft_usleep(philo->data->time_to_die, philo);
	handle_mutexes(philo->fork_left, UNLOCK);
}

void	grabbing_forks(t_philo *philo, t_opcode opcode)
{
	if (philo->philo_id % 2 == 0)
	{
		printf(BLUE "[DEBUG]: Even number of philo is grabbing forks\n" RESET);
		handle_mutexes(philo->fork_left, opcode);
		print_message(philo, FORK);
		handle_mutexes(philo->fork_right, opcode);
		print_message(philo, FORK);
	}
	else
	{
		printf(YELLOW "[DEBUG]: Odd number of philo is grabbing forks\n" RESET);
		handle_mutexes(philo->fork_right, opcode);
		print_message(philo, FORK);
		handle_mutexes(philo->fork_left, opcode);
		print_message(philo, FORK);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:54:52 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/31 17:11:15 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_data(t_global *data)
{
	printf("Number of philosophers: %u\n", data->nbr_of_philo);
	printf("Time to die: %u\n", data->time_to_die);
	printf("Time to eat: %u\n", data->time_to_eat);
	printf("Time to sleep: %u\n", data->time_to_sleep);
	printf("Must eat count %u\n", data->must_eat_count);
	printf("Anybody died? Are philos full?: %d\n", data->end_simul);
}

void	write_status_debug(t_status status, t_philo *philo, long elapsed_time)
{
	if (status == FORK_ONE && !simulation_finished(philo->global_data))
		printf("%-6ld %d has taken 1st fork " CYAN "[id: %u]\n" RESET,
			elapsed_time, philo->philo_id, philo->right_fork->fork_id);
	else if (status == FORK_TWO && !simulation_finished(philo->global_data))
		printf("%-6ld %d has taken 2nd fork " CYAN "[id: %u]\n" RESET,
			elapsed_time, philo->philo_id, philo->left_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->global_data))
		printf("%-6ld %d is eating " YELLOW "[meals eaten: %ld]\n" RESET,
			elapsed_time, philo->philo_id, philo->meals_count);
	else if (status == THINKING && !simulation_finished(philo->global_data))
		printf("%-6ld %d is thinking\n", elapsed_time, philo->philo_id);
	else if (status == SLEEPING && !simulation_finished(philo->global_data))
		printf("%-6ld %d is sleeping\n", elapsed_time, philo->philo_id);
	else if (status == DIED)
		printf(RED "%-6ld %d died\n" RESET, elapsed_time, philo->philo_id);
}
